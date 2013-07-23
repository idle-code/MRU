#include "MruCore.hpp"
#undef NDEBUG_L
#include <debug_l.h>
using namespace mru;

int
main(int argc, char **argv)
{
  FO("main(int argc, char **argv)");
  
  MruCore *core = MruCore::get_instance();

  int result = core->start(argc, argv);
  
  MruCore::destroy_instance();
  return result;
}

