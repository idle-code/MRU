#include "MruCore.hpp"
#undef NDEBUG_L
#include <debug_l.h>
using namespace mru;

int
main(int a_argc, char **a_argv)
{
  FO("main(int a_argc, char **a_argv)");
  
  MruCore *core = MruCore::get_instance();

  int result = core->start(a_argc, a_argv);
  
  MruCore::destroy_instance();
  return result;
}

