#include "metatag_test.hpp"
#include <debug_l.h>

class EchoTag : public Metatag {
public:
  EchoTag(void)
   : Metatag("EchoTag")
  { } 

  bool
  initialize(const UnicodeString &a_arguments)
  {
    FO("EchoTag::Initialize(const UnicodeString &a_arguments)");
    VAL(mru::glue_cast<std::string>(tagName()));
    VAL(mru::glue_cast<std::string>(a_arguments));
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
    return mru::glue_cast<UnicodeString>("<") + a_text + mru::glue_cast<UnicodeString>(">") + mru::glue_cast<UnicodeString>(foo++);
  }

  static int foo;
};

void
metatag_tests::construction(void)
{
  FO("metatag_tests::construction(void)")
  std::list<Metatag*> bindings;
  
  EchoTag echo;
  //bindings.insert(std::make_pair(UnicodeString(), &echo));
  bindings.push_back(&echo);
  UnicodeString result;
  //UnicodeString result = MetatagExpression::evaluate("%EchoTag(arguments...)", bindings);
  //UnicodeString result = MetatagExpression::evaluate("%EchoTag(arguments...){123%EchoTag(){456}}_some_text %EchoTag()", bindings);
  MetatagExpression me("%EchoTag(value=12){%EchoTag(){Ala} ma kota} and some other text");
  me.bind(bindings);
  result = me.evaluate();
  VAL(mru::glue_cast<std::string>(result));
  MSG("----------");
  //VAL(mru::glue_cast<std::string>(me.evaluate()));
  //UnicodeString result = MetatagExpression::evaluate("%Count(start=0)_file_%ToUpper(){%Name(%Nontag(\\))_ma_kota}", bindings);
  //VAL(glue_cast<std::string>(result));
  
}

