#define PLUGIN_HOST
#include "core.hpp"
#include "types.hpp"
#include "plugins/ui_plugin.hpp"
#include "plugins/output_plugin.hpp"
#include "plugins/tag_plugin.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

Core::Core(void)
  : m_ui(NULL), m_out_driver(NULL), m_base_directory("/"), m_current_directory(m_base_directory)
{
  FO("Core::Core(void)");
  prepare_registry();
  registry reg = reg::get_reference(); 

  // create all managers (it is need to be done before any dynamic module could be loaded):
  UiPluginManager::set_instance(new UiPluginManager("UiPlugin", reg["plugins.ui"]));
  OutputPluginManager::set_instance(new OutputPluginManager("OutputPlugin", reg["plugins.output"]));
  TagPluginManager::set_instance(new TagPluginManager("TagPlugin", reg["plugins.tags"]));
}

Core::~Core(void)
{
  FO("Core::~Core(void)");

  // destroy all managers (it's not mandatory (imo) becouse we are exiting anyway...): 
  TagPluginManager::destroy_instance();
  OutputPluginManager::destroy_instance();
  UiPluginManager::destroy_instance();
}

registry
Core::get_registry(void)
{
  return reg::get_reference();
}

int
Core::start(int a_argc, char **a_argv)
{
  FO("Core::start(int a_argc, char **a_argv)");

  parse_command_line(a_argc, a_argv);
  load_configuration();
  load_default_modules();

  registry reg = reg::get_reference(); 
  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  m_ui = ui_manager->create_plugin(reg[".config"].get("ui"));
  m_ui->Init(this);

  if(m_ui == NULL) {
    ERR("Couldn't initialize UI plugin");
    return 1;
  }
  int result = m_ui->start(a_argc, a_argv);
  data_tree::print_tree(reg); 
  return result;
}

/* ------------------------------------------------------------------------- */

void
Core::prepare_registry(void)
{
  FO("prepare_registry(void)");
  registry reg = reg::get_reference(); 
  reg.create(".arguments");
  reg.create(".config");
  reg.create(".plugins");
  reg.create(".plugins.ui");
  reg.create(".plugins.output");
  reg.create(".plugins.tags");
  //reg.create(".reg");
  //reg.create(".reg._info";
  reg.create(".run");
  data_tree::print_tree(reg);
}

namespace
{

void
parse_argument(char *a_string)
{
  if(a_string == NULL)
    return;
  registry reg = reg::get_reference()[".arguments"]; 
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
}

} /* unnamed namespace */

//TODO: rewrite using boost::tokenizer
void
Core::parse_command_line(int a_argc, char **a_argv)
{
  FO("parse_command_line(int &a_argc, char **a_argv)");
  registry reg = reg::get_reference()[".arguments"]; 

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
Core::load_configuration(const filepath_type &a_file)
{
  FO("load_configuration(const filepath_type &a_file)");
  registry reg = reg::get_reference(); 
  
  reg[".config"].set("ui", reg.get_or(".arguments.ui", "wxWidgetsUi"));
  //reg[".config"].set("ui", reg.get_or(".arguments.ui", "TextUi"));
  reg[".config"].set("output_driver", reg.get_or(".arguments.output_driver", "GenericBoost"));

  return true;
}

int
Core::load_default_modules(void)
{
  FO("load_modules(void)");

  int modules_loaded = 0;
  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  modules_loaded += ui_manager->load_module("plugins/ui/TextUi/TextUi");
  modules_loaded += ui_manager->load_module("plugins/ui/wxWidgetsUi/wxWidgetsUi");

  OutputPluginManager *output_manager = OutputPluginManager::get_instance();
  modules_loaded += output_manager->load_module("plugins/output/GenericBoost/GenericBoost");

  TagPluginManager *tag_manager = TagPluginManager::get_instance();
  modules_loaded += tag_manager->load_module("plugins/tags/StandardTags/StandardTags");

  return modules_loaded;
}

/* ------------------------------------------------------------------------- */

bool
Core::set_base_directory(const filepath_type &a_directory)
{
  if(!bfs::exists(a_directory) || !bfs::is_directory(a_directory))
    return false; //TODO: signal error
  m_base_directory = a_directory;
  set_current_directory(a_directory);
  return true;
}

const filepath_type &
Core::get_base_directory(void) const
{
  return m_base_directory;
}

bool
Core::set_current_directory(const filepath_type &a_directory)
{
  if(!bfs::exists(a_directory) || !bfs::is_directory(a_directory))
    return false; //TODO: signal error
  m_current_directory = a_directory;
  return true;
}

const filepath_type &
Core::get_current_directory(void) const
{
  return m_current_directory;
}


bool
Core::start_rename(void)
{

  return false;
}

bool
Core::pause_rename(void)
{

  return false;
}

bool
Core::stop_rename(void)
{

  return false;
}

FileIterator
Core::get_directory_iterator(const filepath_type &a_directory)
{
  return FileIterator(a_directory);
}

/* ------------------------------------------------------------------------- */

UiPlugin *
Core::get_ui_plugin(void)
{
  return m_ui;
}

OutputPlugin *
Core::get_output_plugin(void)
{
  return m_out_driver;
}

} /* namespace mru */

