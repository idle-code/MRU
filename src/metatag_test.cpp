#include "metatag.hpp"
#include "glue.hpp"
#include <debug_l.h>

class EchoTag : public mru::Metatag {
public:
  EchoTag(void)
   : Metatag("EchoTag")
  { } 

  bool
  Initialize(const UnicodeString &a_arguments)
  {
    FO("EchoTag::Initialize(const UnicodeString &a_arguments)");
    VAL(mru::glue_cast<std::string>(a_arguments));
    VAL(mru::glue_cast<std::string>(name()));
    return true;
  }

  UnicodeString
  operator()(void)
  {
    FO("EchoTag::operator(void)");
    return mru::glue_cast<UnicodeString>("<none>");
  }

  UnicodeString
  operator()(const UnicodeString &a_text)
  {
    FO("EchoTag::operator(const UnicodeString &a_text)");
    VAL(mru::glue_cast<std::string>(a_text));
    return mru::glue_cast<UnicodeString>("<") + a_text + mru::glue_cast<UnicodeString>(">");
  }

};

int
main(int argc, char const *argv[])
{
  using namespace mru;
  FO("main()");

  std::map<UnicodeString, Metatag*> bindings;
  
  EchoTag echo;
  bindings.insert(std::make_pair(UnicodeString(), &echo));
  bindings.insert(std::make_pair(glue_cast<UnicodeString>("EchoTag"), &echo));

  //UnicodeString result = MetatagExpression::evaluate("%EchoTag(arguments...)", bindings);
  UnicodeString result = MetatagExpression::evaluate("%EchoTag(arguments...){123%EchoTag(){456}}_some_text %EchoTag(){}", bindings);
  //UnicodeString result = MetatagExpression::evaluate("%Count(start=0)_file_%ToUpper(){%Name(%Nontag(\\))_ma_kota}", bindings);
  VAL(glue_cast<std::string>(result));

  return 0;
}

