#include "core.hpp"
#undef NDEBUG_L
#include <debug_l.h>
using namespace mru;

int
main(int a_argc, char **a_argv)
{
  FO("main(int a_argc, char **a_argv)");
  
  //MSG(UnicodeString2STLString(UNICODE_STRING_SIMPLE("/some/path.to_file")));
  //return 0;

  Core *core = Core::get_instance();

  int result = 0;
  result = core->start(a_argc, a_argv);
  
  Core::destroy_instance();
  return result;
}

