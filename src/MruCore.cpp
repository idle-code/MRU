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
  : m_ui(NULL), m_out_driver(NULL), m_base_directory("/"), m_current_directory(m_base_directory)
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

  TagPluginManager *tag_manager = TagPluginManager::get_instance();
  modules_loaded += tag_manager->load_module("plugins/tags/StandardTags/StandardTags");

  return modules_loaded;
}

/* ------------------------------------------------------------------------- */

bool
MruCore::set_base_directory(const filepath_type &a_directory)
{
  if(!bfs::exists(a_directory) || !bfs::is_directory(a_directory))
    return false; //TODO: signal error
  m_base_directory = a_directory;
  set_current_directory(a_directory);
  return true;
}

const filepath_type &
MruCore::get_base_directory(void) const
{
  return m_base_directory;
}

bool
MruCore::set_current_directory(const filepath_type &a_directory)
{
  if(!bfs::exists(a_directory) || !bfs::is_directory(a_directory))
    return false; //TODO: signal error
  m_current_directory = a_directory;
  return true;
}

const filepath_type &
MruCore::get_current_directory(void) const
{
  return m_current_directory;
}


void
MruCore::start_rename(void)
{
  FO("MruCore::start_rename(void)");
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
}

FileIterator
MruCore::get_directory_iterator(const filepath_type &a_directory)
{
  return FileIterator(a_directory);
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

} /* namespace mru */

