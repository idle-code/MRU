#define PLUGIN_HOST
#include <plugin_manager.hpp>
#include <plugins/ui_plugin.hpp>
#undef NDEBUG_L
#include <debug_l.h>
#include <boost/program_options.hpp>
using namespace mru;
namespace po = boost::program_options;

void prepare_registry(void);
void parse_command_line(int &a_argc, char **&a_argv);
void setup_default_plugins(void);

int
main(int a_argc, char **a_argv)
{
  FO("main(int a_argc, char **a_argv)");
  prepare_registry();
  UiPluginManager::set_instance(new UiPluginManager("UiPlugin", reg::get_reference()["plugins.ui"]));

  parse_command_line(a_argc, a_argv);
  setup_default_plugins();

  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  UiPlugin *ui = ui_manager->create_plugin("TextUi"); //FIXME: select gui by command line or config file 
  
  if(ui == NULL) {
    ERR("Could not initialize user interface (plugin)");
    return 1;
  }

  int result = ui->start(a_argc, a_argv);
  data_tree::print_tree(*reg::get_instance());
  
  UiPluginManager::destroy_instance();
  return result;
}

/* ------------------------------------------------------------------------- */

void
prepare_registry(void)
{
  FO("prepare_registry(void)");
  registry reg = reg::get_reference(); 
  reg.create(".arguments", registry::value_type::None);
  reg.create(".config", registry::value_type::None);
  reg.create(".plugins", registry::value_type::None);
  reg.create(".plugins.ui", registry::value_type::None);
  reg.create(".plugins.filesystem", registry::value_type::None);
  reg.create(".plugins.tags", registry::value_type::None);
  reg.create(".reg", registry::value_type::None);
  reg.create(".reg._info", "Reserved for future use");
  reg.create(".tmp", registry::value_type::None);
  data_tree::print_tree(reg);
}

void
parse_command_line(int &a_argc, char **&a_argv)
{
  FO("parse_command_line(int &a_argc, char **&a_argv)");
  registry reg = reg::get_reference()[".arguments"]; 

}

void
setup_default_plugins(void)
{
  FO("setup_default_plugins(void)");
  UiPluginManager *ui_manager = UiPluginManager::get_instance();
  ui_manager->load_module("plugins/ui/TextUi/TextUi");

}

