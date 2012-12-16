#define PLUGIN_HOST
#include "test_module.hpp"
#include <debug_l.h>

int
main(int argc, char const *argv[])
{
  DEBUG_L_FILTER(debug_l::lAll);
  FO("main()");
  using namespace mru;
  (void)MyPluginManager::get_instance("MyPlugin");
  (void)YourPluginManager::get_instance("YourPlugin");

  MyPluginManager* my_pm = MyPluginManager::get_instance();
  YourPluginManager* your_pm = YourPluginManager::get_instance();

  VAL(my_pm);
  VAL(your_pm);

  if(0 == my_pm->load_module("./test_module1")) {
    ERR("No module named test_module1 found");
    //return 1;
  }

  if(0 == your_pm->load_module("./test_module2")) {
    ERR("No module named test_module2 found");
    //return 2;
  }

  MyPlugin *mplg1 = my_pm->get_plugin("MPlg1");
  MyPlugin *mplg2 = my_pm->get_plugin("MPlg2");
  YourPlugin *yplg = your_pm->get_plugin("YPlg");
  VAL(mplg1);

  if(mplg1)
    mplg1->say_hello();
  if(mplg2)
    mplg2->say_hello();
  if(yplg)
    yplg->say_goodbye();
  
  return 0;
}
