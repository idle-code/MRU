#define PLUGIN_HOST
#include "MruCore.hpp"
#include "types.hpp"
#include "plugins/UiPlugin.hpp"
#include "plugins/InputPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/MetatagPlugin.hpp"
#undef NDEBUG_L
#include <debug_l.h>
#include <unistd.h>

namespace mru
{

  /*
MruException::MruException(const std::string &a_module, const UnicodeString &a_message)
  : m_module(a_module), m_message(a_message)
{ }

MruException::MruException(const std::string &a_module, const std::string &a_message)
  : m_module(a_module), m_message(glue_cast<UnicodeString>(a_message))
{ }

MruException::~MruException(void) throw()
{ }

const char *
MruException::what(void) const throw()
{
  return glue_cast<std::string>(m_message).c_str();
}

const UnicodeString &
MruException::message(void) const throw()
{
  return m_message;
}
*/

/* ------------------------------------------------------------------------- */

MruCore::MruCore(void)
  : m_ui(NULL), m_output(NULL),
    m_directory("/home/idlecode/projects/mru/src/tests/files"),
    m_bindings_outdated(true)
{
  FO("MruCore::MruCore(void)");

  // create all managers (it is need to be done before any dynamic module could be loaded):
  UiPluginManager::set_instance(new UiPluginManager("UiPlugin"));
  InputPluginManager::set_instance(new InputPluginManager("InputPlugin"));
  OutputPluginManager::set_instance(new OutputPluginManager("OutputPlugin"));
  MetatagPluginManager::set_instance(new MetatagPluginManager("MetatagPlugin"));
}

MruCore::~MruCore(void)
{
  FO("MruCore::~MruCore(void)");

  // destroy all managers (it's not mandatory (imo) becouse we are exiting anyway...): 
  MetatagPluginManager::destroy_instance();
  OutputPluginManager::destroy_instance();
  InputPluginManager::destroy_instance();
  UiPluginManager::destroy_instance();
}

int
MruCore::start(int a_argc, char **a_argv)
{
  FO("MruCore::start(int a_argc, char **a_argv)");

  //TODO: add command line parsing

  loadConfiguration("./MRU.conf");
  registry reg = reg::get_reference(); 
  if(a_argc > 2 && std::string(a_argv[1]) == "-u")
    reg.put("config.ui", a_argv[2]);

  assert(getUiPlugin() != NULL && "No UiPlugin specified");
  return getUiPlugin()->start(a_argc, a_argv);
}

/* ------------------------------------------------------------------------- */

registry&
MruCore::getRegistry(void)
{
  return reg::get_reference();
}

bool
MruCore::loadConfiguration(const FilePath &a_file)
{
  FO("MruCore::loadConfiguration(const FilePath &a_file)");
  registry reg = reg::get_reference(); 
  
  reg.put("module.path", "./plugins");
  reg.put("module.ui", "wxWidgetsUi");
  //reg.put("config.ui", reg.get("config.ui", "TextUi"));
  reg.put("module.input", "BoostInputPlugin");
  reg.put("module.output", "GenericBoost");

  return true;
}

int
MruCore::loadDefaultModules(void)
{
  registry reg = reg::get_reference(); 
  int modules_loaded = 0;
  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  //modules_loaded += ui_manager->load_module(reg.get<std::string>("module.path") + "/ui/TextUi/TextUi");
  modules_loaded += ui_manager->load_module(reg.get<std::string>("module.path") + "/ui/wxWidgetsUi/libwxWidgetsUi.so");

  InputPluginManager *input_manager = InputPluginManager::get_instance();
  modules_loaded += input_manager->load_module(reg.get<std::string>("module.path") + "/input/BoostInputPlugin/libBoostInputPlugin.so");

  OutputPluginManager *output_manager = OutputPluginManager::get_instance();
  modules_loaded += output_manager->load_module(reg.get<std::string>("module.path") + "/output/GenericBoost/libGenericBoost.so");

  modules_loaded += loadMetatags();
  return modules_loaded;
}

namespace
{

class metatag_factory_wrapper : public abstract_factory<Metatag> {
public:
  metatag_factory_wrapper(plugin_factory<MetatagPlugin> *a_plugin_factory)
    : m_plugin_factory(a_plugin_factory)
  { }

  Metatag* create(void)
  {
    return reinterpret_cast<MetatagPlugin*>(m_plugin_factory->create());
  } 

  void destroy(Metatag *a_instance)
  {
    m_plugin_factory->destroy(static_cast<MetatagPlugin*>(a_instance));
  }
private:
  plugin_factory<MetatagPlugin> *m_plugin_factory;
};

} /* anonymous namespace */

int
MruCore::loadMetatags(void)
{
  registry reg = getRegistry();
  MetatagPluginManager *tag_manager = MetatagPluginManager::get_instance();
  int tags_loaded = 0;
  tags_loaded += tag_manager->load_module(reg.get<std::string>("module.path") + "/tags/StandardMetatags/StandardMetatags");
  tags_loaded += tag_manager->load_module(reg.get<std::string>("module.path") + "/tags/AudioMetatag/AudioMetatag");

  return tags_loaded;
}

/* ------------------------------------------------------------------------- */

void
MruCore::setMetatagExpression(const UnicodeString &a_expression)
{
  FO("MruCore::set_metatag_expression(const UnicodeString &a_expression)");
}

void
MruCore::bindMetatags(void)
{
}

UnicodeString
MruCore::getMetatagExpression(void)
{
}

void
MruCore::resetState(void)
{
}

/* ------------------------------------------------------------------------- */

void *
worker_thread_main(void *a_core_pointer)
{
  FO("worker_thread_main(void *a_core_pointer)");
  MruCore *core = reinterpret_cast<MruCore*>(a_core_pointer);
  FileIterator::Pointer dir_iterator = core->getIterator();
  FilePath old_path;
  FilePath new_path;

  OutputPlugin *output_driver = core->getOutputPlugin();
  if(output_driver == NULL) {
    ERR("No valid output driver configured"); 
    return NULL;
  }

  core->SignalRenameStarted();
  //TODO
  core->SignalRenameStopped();
  return NULL;
}

void
MruCore::startRename(void)
{
  resetState();
  if(0 != pthread_create(&m_worker_thread, NULL, &worker_thread_main, this)) {
    ERR("Couldn't create worker thread!");
  }
}

void
MruCore::stopRename(void)
{
  if(0 != pthread_join(m_worker_thread, NULL)) {
    WARN("pthread_join failed (thread might already be stopped)");
  }
  resetState();
}

/* ------------------------------------------------------------------------- */

FileIterator::Pointer
MruCore::getIterator(void)
{
  try {
    return m_input->getFileIterator(getDirectory());
  } catch(...) {
    ERR("Couldn't get directory iterator for: " << getDirectory());
    return FileIterator::Pointer();
  }
}

FilePath
MruCore::generateNewFilepath(const FileIterator *a_iterator)
{
  assert(a_iterator != NULL && "FileIterator == NULL");

  return FilePath();
}

/* ------------------------------------------------------------------------- */

UiPlugin *
MruCore::getUiPlugin(void)
{
  return m_ui;
}

OutputPlugin *
MruCore::getOutputPlugin(void)
{
  return m_output;
}

std::list<std::string>
MruCore::getAvailableMetatags(void)
{
  return MetatagPluginManager::get_instance()->available_plugins();
}

void
MruCore::setDirectory(const FilePath &a_directory)
{
  if(m_directory != a_directory) {
    m_directory = a_directory;
    SignalDirectoryChanged(m_directory);
  }
}

const FilePath &
MruCore::getDirectory(void) const
{
  return m_directory;
}

} /* namespace mru */

