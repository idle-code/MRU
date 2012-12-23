#include "TextUi.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

TextUi::TextUi(void)
  : UiPlugin("TextUi")
{ }

TextUi::~TextUi(void)
{ }

int
TextUi::start(int a_argc, char *a_argv[])
{
  FO("TextUi::start(int a_argc, char *a_argv[])");

  return 0;
}

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::TextUi)
EXPORT_END

