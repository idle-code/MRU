#include "hello_plugin.hpp"
#include <debug_l.h>

int
main(int argc, char const *argv[])
{
  FO("main()");
  HelloPluginManager hpm;
  hpm.load("./hello_plugin");
  HelloPlugin *first = hpm.get_plugin("HelloPlugin");
  data_tree::print_tree(hpm.tree());

  VAL(first);
  return 0;
}

