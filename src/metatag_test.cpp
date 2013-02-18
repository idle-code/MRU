#include "metatag.hpp"
#include "glue.hpp"
#include <debug_l.h>

int
main(int argc, char const *argv[])
{
  using namespace mru;
  FO("main()");

  std::map<UnicodeString, Metatag*> bindings;

  UnicodeString result = MetatagExpression::evaluate("%Count(start=0)_file_%ToUpper(){%Name(_ma_kota)}%Ala", bindings);
  VAL(glue_cast<std::string>(result));

  return 0;
}

