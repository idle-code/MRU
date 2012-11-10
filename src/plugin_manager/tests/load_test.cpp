#include "test_module.hpp"
#include <debug_l.h>

void print_tree(const my_plugin_manager::data_tree &a_tree, int indent = 0)
{
  if(a_tree.size() < 1)
    return;
  my_plugin_manager::data_tree::const_node_iterator ci = a_tree.begin();
  std::string ind;
  for(; ci != a_tree.end(); ++ci) {
    for(int i = 0; i < indent; ++i)
      ind += "  ";
    MSG(ind + ci.name());
    print_tree(*ci, indent+1);
  }
}

int
main(int argc, char const *argv[])
{
  DEBUG_L_FILTER(debug_l::lAll);
  FO("main()");
  using namespace mru;

  my_plugin_manager pm;
  print_tree(pm.tree());

  MyPlugin *module_1 = pm.load("test_module1.so");  
  MyPlugin *module_2 = pm.load("test_module1");  
  //MyPlugin *module_1 = pm.load("libtest_module1.so");  

  if(module_1 == NULL) {
    ERR("No module named test_module1 found");
    return 1;
  }
  MSG("-----------------------------------------");
  module_1->say_hello();
  print_tree(pm.tree());

  pm.unload(module_1);

  return 0;
}
