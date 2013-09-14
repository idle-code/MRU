#include "MruCore.hpp"
#undef NDEBUG_L
#include <debug_l.h>
#include "MetatagBase.hpp"

#include "plugins/InputPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/UiPlugin.hpp"

#include "DllModule.hpp"
#include "BsdDllModule.hpp"

#include <boost/property_tree/xml_parser.hpp>

namespace mru {


MruCore::MruCore(void)
{
  // create all managers (it is need to be done before any dynamic module could be loaded):
  input_plugin_manager = InputPlugin::Manager::create();
  output_plugin_manager = OutputPlugin::Manager::create();
  ui_plugin_manager = UiPlugin::Manager::create();
  metatag_plugin_manager = MetatagPluginManager::create();

  loadDefaultConfiguration();
}

MruCore::~MruCore(void)
{
  FO("MruCore::~MruCore(void)");
  saveConfiguration();
}

void
MruCore::saveConfiguration(void)
{
  FilePath configuration_file = reg.get<FilePath>("configuration_file");
  MSG("Saving configuration to: " << glue_cast<std::string>(configuration_file));
  try {
    boost::property_tree::write_xml(glue_cast<std::string>(configuration_file), reg, std::locale(), boost::property_tree::xml_parser::xml_writer_make_settings(' ', 2));
  } catch (boost::property_tree::file_parser_error &fpe) {
    ERR("Couldn't save configuration file '" << fpe.filename() << "': " << fpe.message() << " (at " << fpe.line() << ")");
  }
}

int
MruCore::start(int argc, char **argv)
{
  FO("MruCore::start(void)");

  loadAllModulesIn<InputPlugin>(reg.get<std::string>("plugin.input.directory"), input_plugin_manager);
  loadAllModulesIn<OutputPlugin>(reg.get<std::string>("plugin.output.directory"), output_plugin_manager);
  loadAllModulesIn<UiPlugin>(reg.get<std::string>("plugin.ui.directory"), ui_plugin_manager);

  if (!getInputPlugin()) {
    InputPlugin::Pointer input_plugin = input_plugin_manager->createPlugin(reg.get<std::string>("plugin.input"));

    if (!input_plugin)
      throw Exception("No valid input plugin specified");
    setInputPlugin(input_plugin);
  }

  if (!getOutputPlugin()) {
    OutputPlugin::Pointer output_plugin = output_plugin_manager->createPlugin(reg.get<std::string>("plugin.output"));

    if (!output_plugin)
      throw Exception("No valid output plugin specified");
    setOutputPlugin(output_plugin);
  }

  if (!getUiPlugin()) {
    UiPlugin::Pointer ui_plugin = ui_plugin_manager->createPlugin(reg.get<std::string>("plugin.ui"));

    if (!ui_plugin)
      throw Exception("No valid UI plugin specified");
    setUiPlugin(ui_plugin);
  }

  return getUiPlugin()->start(argc, argv);
}

template<typename PluginType>
void
MruCore::loadAllModulesIn(const FilePath &directory, typename PluginType::Manager::Pointer plugin_manager)
{
  std::list<FilePath> file_list = listFilesInDirectory(directory);

  std::list<FilePath>::const_iterator file_iter = file_list.begin();
  std::list<FilePath>::const_iterator end = file_list.end();
  for(; file_iter != end; ++file_iter) {
    try {
      loadModule<PluginType>(*file_iter, plugin_manager);
    } catch (DllModule::Exception &e) {
      WARN(e.getMessage());
    }
  }
}

template<typename PluginType>
void
MruCore::loadModule(const FilePath &module_path, typename PluginType::Manager::Pointer plugin_manager)
{
  MSG("Loading '" << module_path << "'...");
  typename DllModule::Pointer plugin_dll = BsdDllModule::create();
  plugin_dll->load(module_path);

  typename PluginType::RegisterFunctionType register_function = plugin_dll->get<typename PluginType::RegisterFunctionType>(PluginType::RegisterFunctionName());
  if (!register_function)
    throw Exception(glue_cast<UnicodeString>("No '") + PluginType::RegisterFunctionName() + "' method exported in module: " + module_path.c_str());

  register_function(plugin_manager);
}

std::list<FilePath>
MruCore::listFilesInDirectory(const FilePath &directory)
{
  std::list<FilePath> file_list;

  if (bfs::exists(directory) && bfs::is_directory(directory)) {
    bfs::directory_iterator end_iter;
    for (bfs::directory_iterator iter(directory); iter != end_iter; ++iter) {
      if (bfs::is_regular_file(iter->status())) {
        file_list.push_back(*iter);
      }
    }
  }

  return file_list;
}

void
MruCore::loadConfiguration(const FilePath &configuration_file)
{
  FO("MruCore::loadConfiguration(void)");
  MSG("Reading configuration from: " << configuration_file);
  try {
    boost::property_tree::read_xml(reg.get<std::string>("configuration_file"), reg);
    reg.put("configuration_file", configuration_file.generic_string());
  } catch (boost::property_tree::file_parser_error &fpe) { //FIXME: catch (and ignore) proper exception
    WARN("Couldn't read configuration from: " << fpe.filename() << ": " << fpe.message() << " (at " << fpe.line() << ")");
  }
}

UiPlugin::Pointer
MruCore::getUiPlugin(void)
{
  return ui_plugin;
}

void
MruCore::setUiPlugin(UiPlugin::Pointer plugin)
{
  ui_plugin = plugin;
}

OutputPlugin::Pointer
MruCore::getOutputPlugin(void)
{
  return output_plugin;
}

void
MruCore::setOutputPlugin(OutputPlugin::Pointer plugin)
{
  output_plugin = plugin;
}

InputPlugin::Pointer
MruCore::getInputPlugin(void)
{
  return input_plugin;
}

void
MruCore::setInputPlugin(InputPlugin::Pointer plugin)
{
  input_plugin = plugin;
}

/* ------------------------------------------------------------------------- */

void
MruCore::setMetatagExpression(Metatag::Expression::Pointer expression)
{

}

Metatag::Expression::Pointer
MruCore::getMetatagExpression(void)
{
  return Metatag::Expression::Pointer();
}

void
MruCore::resetState(void)
{

}

/* ------------------------------------------------------------------------- */

void
MruCore::startRename(void)
{
}

void
MruCore::stopRename(void)
{
}

/* ------------------------------------------------------------------------- */

FileIterator::Pointer
MruCore::getIterator(void)
{
  assert(input_plugin);
  try {
    return input_plugin->getFileIterator(getDirectory());
  } catch(...) {
    ERR("Couldn't get directory iterator for: " << getDirectory());
    return FileIterator::Pointer();
  }
}

FilePath
MruCore::generateNewFilepath(const FileIterator::Pointer file_iterator)
{
  assert(file_iterator && "file_iterator == NULL");

  return FilePath();
}

/* ------------------------------------------------------------------------- */

void
MruCore::setDirectory(const FilePath &directory)
{
  reg.put("run.directory", directory.generic_string());
  SignalDirectoryChanged(directory);
}

const FilePath
MruCore::getDirectory(void) const
{
  return reg.get<FilePath>("run.directory");
}

} /* namespace mru */

