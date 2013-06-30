#define PLUGIN_HOST
#include "MruCore.hpp"
#include "types.hpp"
#include "plugins/UiPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/TagPlugin.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

MruCore::MruCore(void)
  : m_ui(NULL), m_out_driver(NULL),
    m_base_directory("/home/idlecode/projects/mru/src/tests/files"), m_current_directory(m_base_directory),
    m_include_directories(false), m_include_filenames(true), m_work_on_directories(false),
    m_bindings_outdated(true)

{
  FO("MruCore::MruCore(void)");

  // create all managers (it is need to be done before any dynamic module could be loaded):
  UiPluginManager::set_instance(new UiPluginManager("UiPlugin"));
  OutputPluginManager::set_instance(new OutputPluginManager("OutputPlugin"));
  TagPluginManager::set_instance(new TagPluginManager("TagPlugin"));
}

MruCore::~MruCore(void)
{
  FO("MruCore::~MruCore(void)");

  // destroy all managers (it's not mandatory (imo) becouse we are exiting anyway...): 
  TagPluginManager::destroy_instance();
  OutputPluginManager::destroy_instance();
  UiPluginManager::destroy_instance();
}

int
MruCore::start(int a_argc, char **a_argv)
{
  FO("MruCore::start(int a_argc, char **a_argv)");

  parse_command_line(a_argc, a_argv);
  load_configuration();
  load_default_modules();
  
  registry reg = reg::get_reference(); 
  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  m_ui = ui_manager->create_plugin(reg.get<std::string>(".config.ui", "wxWidgetsUi"));
  m_ui->Init(this);

  if(m_ui == NULL) {
    ERR("Couldn't initialize UI plugin");
    return 1;
  }
  int result = m_ui->start(a_argc, a_argv);
  return result;
}

/* ------------------------------------------------------------------------- */

registry&
MruCore::get_registry(void)
{
  return reg::get_reference();
}

void
MruCore::include_directories(bool enable)
{
  m_include_directories = enable;
}

bool
MruCore::include_directories(void) const
{
  return m_include_directories;
}

void
MruCore::include_filenames(bool enable)
{
  m_include_filenames = enable;
}

bool
MruCore::include_filenames(void) const
{
  return m_include_filenames;
}

void
MruCore::work_on_directories(bool enable)
{
  m_work_on_directories = enable;
}

bool
MruCore::work_on_directories(void) const
{
  return m_work_on_directories;
}

namespace
{

void
parse_argument(char *a_string)
{
  if(a_string == NULL)
    return;

  /*
  MSG("Parsing: " << a_string);
  mru::string_type arg = a_string;

  if(arg.startsWith(UNICODE_STRING_SIMPLE("--"))) {
    arg.remove(0, 2); //remove prefix 
  } else if(arg.startsWith(UNICODE_STRING_SIMPLE("-"))) {
    arg.remove(0, 1); //FIXME: differently treat options shortcuts?
  }

  if(arg.length() < 1)
    return;

  int32_t equal_sign_index = arg.indexOf('=');
  if(equal_sign_index != -1) { //key=value syntax
    mru::string_type key = arg.tempSubString(0, equal_sign_index); 
    mru::string_type value = arg.tempSubString(equal_sign_index + 1); 

    if(key.length() > 0) {
      //FIXME: conversion is needed to store UTF strings into registry tree:
      registry::value_type::text_type bare_key;
      key.toUTF8String(bare_key);
      registry::value_type::text_type bare_value;
      value.toUTF8String(bare_value);

      if(registry::path_type().is_valid_name(bare_key))
        reg.set(bare_key, bare_value);
    }
  } else { //simple property
      registry::value_type::text_type bare_key;
      arg.toUTF8String(bare_key);
      if(registry::path_type().is_valid_name(bare_key))
        reg.set(bare_key, registry::value_type::None);
  }
  //*/
}

} /* unnamed namespace */

//TODO: rewrite using boost::tokenizer
void
MruCore::parse_command_line(int a_argc, char **a_argv)
{
  FO("parse_command_line(int &a_argc, char **a_argv)");
  //registry reg = reg::get_reference()[".arguments"]; 

  //po::options_description desc("Usage: ");
  //desc.add_options()
  //  ("help", "show this message")
  //  ("ui", po::value<std::string>(), "user interface to use");
  //
  //po::variables_map vm;
  //po::store(po::parse_command_line(a_argc, a_argv, desc), vm);
  //po::notify(vm);

  for(int i = 0; i < a_argc; ++i) {
    parse_argument(a_argv[i]); 
  }
}

bool
MruCore::load_configuration(const filepath_type &a_file)
{
  FO("load_configuration(const filepath_type &a_file)");
  registry reg = reg::get_reference(); 
  
  reg.put("config.ui", reg.get("config.ui", "wxWidgetsUi"));
  //reg.put("config.ui", reg.get("config.ui", "TextUi"));
  reg.put("config.output_driver", reg.get("config.output_driver", "GenericBoost"));

  return true;
}

int
MruCore::load_default_modules(void)
{
  FO("load_modules(void)");

  int modules_loaded = 0;
  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  modules_loaded += ui_manager->load_module("plugins/ui/TextUi/TextUi");
  modules_loaded += ui_manager->load_module("plugins/ui/wxWidgetsUi/wxWidgetsUi");

  OutputPluginManager *output_manager = OutputPluginManager::get_instance();
  modules_loaded += output_manager->load_module("plugins/output/GenericBoost/GenericBoost");

  modules_loaded += load_tags();
  return modules_loaded;
}

namespace
{

class metatag_factory_wrapper : public abstract_factory<Metatag> {
public:
  metatag_factory_wrapper(plugin_factory<TagPlugin> *a_plugin_factory)
    : m_plugin_factory(a_plugin_factory)
  { }

  Metatag* create(void)
  {
    return reinterpret_cast<TagPlugin*>(m_plugin_factory->create());
  } 

  void destroy(Metatag *a_instance)
  {
    m_plugin_factory->destroy(static_cast<TagPlugin*>(a_instance));
  }
private:
  plugin_factory<TagPlugin> *m_plugin_factory;
};

} /* anonymous namespace */

int
MruCore::load_tags(void)
{
  TagPluginManager *tag_manager = TagPluginManager::get_instance();
  int tags_loaded = 0;
  tags_loaded += tag_manager->load_module("plugins/tags/StandardTags/StandardTags");

  return tags_loaded;
}

/* ------------------------------------------------------------------------- */

void
MruCore::set_base_directory(const filepath_type &a_directory)
{
  if(!bfs::exists(a_directory) || !bfs::is_directory(a_directory))
    return; //TODO: signal error
  m_base_directory = a_directory;
  set_current_directory(a_directory);
}

const filepath_type &
MruCore::get_base_directory(void) const
{
  return m_base_directory;
}

void
MruCore::set_current_directory(const filepath_type &a_directory)
{
  if(!bfs::exists(a_directory) || !bfs::is_directory(a_directory))
    return; //TODO: signal error
  m_current_directory = a_directory;
}

const filepath_type &
MruCore::get_current_directory(void) const
{
  return m_current_directory;
}

void
MruCore::set_metatag_expression(const UnicodeString &a_expression)
{
  FO("MruCore::set_metatag_expression(const UnicodeString &a_expression)");
  m_metatag_expression = MetatagExpression::parse(a_expression);
  m_bindings_outdated = true;
  bind_metatags();
}

void
MruCore::bind_metatags(void)
{
  if(!m_bindings_outdated)
    return;
  FO("MruCore::bind_metatags(void)");
  TagPluginManager *tag_manager = TagPluginManager::get_instance();
  MetatagExpression::bindings_map metatags_bindings;
  std::list<name_type> tag_name_list = tag_manager->available_plugins();
  for(std::list<name_type>::iterator tag_name = tag_name_list.begin(); tag_name != tag_name_list.end(); ++tag_name) {
    //VAL(glue_cast<std::string>(glue_cast<UnicodeString>(*tag_name)));
    metatags_bindings.insert(std::make_pair(glue_cast<UnicodeString>(*tag_name), new metatag_factory_wrapper(tag_manager->get_factory(*tag_name))));
  }
  //VAL(metatags_bindings.size());
  m_metatag_expression.bindings(metatags_bindings);
  m_bindings_outdated = false;
}

UnicodeString
MruCore::get_metatag_expression(void)
{
  return m_metatag_expression.str();
}

void
MruCore::reset_state(void)
{
  m_metatag_expression.reset();
}

void
MruCore::start_rename(void)
{
  FO("MruCore::start_rename(void)");
  reset_state();
}

void
MruCore::pause_rename(void)
{
  FO("MruCore::pause_rename(void)");
}

void
MruCore::stop_rename(void)
{
  FO("MruCore::stop_rename(void)");
  reset_state();
}

FileIterator
MruCore::get_directory_iterator(void)
{
  FO("MruCore::get_directory_iterator(void)");
  try {
    return FileIterator(get_current_directory(), include_directories(), include_filenames());
  } catch(...) {
    ERR("Couldn't get directory iterator for: " << get_current_directory());
    return FileIterator();
  }
}

UnicodeString
MruCore::generate_filepath(const FileIterator &a_iterator)
{
  FO("MruCore::generate_filepath(const FileIterator &a_iterator)");
  if(a_iterator == FileIterator()) // if invalid iterator
    return UnicodeString();
  bind_metatags();
  return m_metatag_expression.evaluate(a_iterator.base_filename()); 
}

/* ------------------------------------------------------------------------- */

UiPlugin *
MruCore::get_ui_plugin(void)
{
  return m_ui;
}

OutputPlugin *
MruCore::get_output_plugin(void)
{
  return m_out_driver;
}

std::list<UnicodeString>
MruCore::get_available_metatags(void)
{
  std::list<name_type> tag_name_list = TagPluginManager::get_instance()->available_plugins();
  std::list<UnicodeString> result;
  for(std::list<name_type>::iterator tag_name = tag_name_list.begin(); tag_name != tag_name_list.end(); ++tag_name) {
    result.push_back(glue_cast<UnicodeString>(*tag_name));
  }
  return result;
}

} /* namespace mru */

