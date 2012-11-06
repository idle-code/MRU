#include "test_module.hpp"
#include <debug_l.h>

int
main(int argc, char const *argv[])
{
  FO("main()");
  using namespace mru;

  my_plugin_manager pm;
  
  MyPlugin *module_1 = pm.load("test_module1");  

  if(module_1 == NULL) {
    ERR("No module named test_module1 found");
    return 1;
  }
  module_1->say_hello();
  pm.unload(module_1);
  return 0;
}
