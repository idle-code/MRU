#include "test_module.hpp"
#include <debug_l.h>

int
main(int argc, char const *argv[])
{
  DEBUG_L_FILTER(debug_l::lAll);
  FO("main()");
  using namespace mru;

  MyPluginManager pm;
  data_tree::print_tree(pm.tree());

  if(0 == pm.load("./test_module1")) {
    ERR("No module named test_module1 found");
    return 1;
  }

  if(0 == pm.load("./test_module2")) {
    ERR("No module named test_module2 found");
    //return 2;
  }

  MyPlugin *plugin_1 = pm.get_plugin("TestPlugin1");
  MyPlugin *plugin_2 = pm.get_plugin("TestPlugin2");
  MyPlugin *plugin_3 = pm.get_plugin("TestPlugin3");

  data_tree::print_tree(pm.tree());

  VAL(plugin_1);
  if(plugin_1 == NULL) {
    ERR("No plugin named TestPlugin1 found");
    return 1;
  } else
    plugin_1->say_hello();
  VAL(plugin_2);
  if(plugin_2 == NULL) {
    ERR("No plugin named TestPlugin2 found");
    //return 2;
  } else
    plugin_2->say_hello();
  VAL(plugin_3);
  if(plugin_3 == NULL) {
    ERR("No plugin named TestPlugin3 found");
    //return 3;
  } else
    plugin_3->say_hello();


  MSG("-----------------------------------------");

  pm.entrypoint("main.after_init")(123); 
  //ENTRYPOINT(pm, "main.after_init", 

  MSG("-----------------------------------------");

  {
    FO("main::before_exit");
    pm.entrypoint("main.before_exit")("Exiting...");
  }
  data_tree::print_tree(pm.tree());

  return 0;
}
