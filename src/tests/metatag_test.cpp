#include "metatag_test.hpp"
#include "glue.hpp"
#include "patterns.hpp"
#include <debug_l.h>
#include <cppunit/ui/text/TestRunner.h>
#include <memory>

//*
class EchoTag : public Metatag {
public:
  typedef EchoTag self_type;
  typedef Metatag parent_type;
public:
  EchoTag(void)
   : Metatag("EchoTag")
  { } 

  void
  initialize(const UnicodeString &a_arguments)
  {
    FO("EchoTag::initialize(const UnicodeString &a_arguments)");
    VAL(this);
    VAL(mru::glue_cast<std::string>(a_arguments));
  }

  UnicodeString
  execute(const UnicodeString &a_area_of_effect)
  {
    FO("EchoTag::execute(const UnicodeString &a_area_of_effect)");
    VAL(mru::glue_cast<std::string>(a_area_of_effect));
    return mru::glue_cast<UnicodeString>("<") + a_area_of_effect + mru::glue_cast<UnicodeString>(">");
  }
};

class CountTag : public Metatag {
public:
  typedef CountTag self_type;
  typedef Metatag parent_type;

  static int counter;
public:
  CountTag(void)
   : Metatag("CountTag")
  { } 

  void
  initialize(const UnicodeString &a_arguments)
  {
    //FO("CountTag::initialize(const UnicodeString &a_arguments)");
    //VAL(this);
    //VAL(mru::glue_cast<std::string>(a_arguments));
  }

  UnicodeString
  execute(const UnicodeString &a_area_of_effect)
  {
    //FO("CountTag::execute(const UnicodeString &a_area_of_effect)");
    //VAL(mru::glue_cast<std::string>(a_area_of_effect));
    return glue_cast<UnicodeString>(counter++);
  }
};

int CountTag::counter = 0;
//*/

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
  MetatagExpression me = MetatagExpression::parse("File_%Count().txt");
  typedef std::map<UnicodeString, abstract_factory<Metatag>* > metatag_bindings;
  metatag_bindings tag_map = me.bindings();

  MSG("Metatags used in expression:");
  for(metatag_bindings::iterator i = tag_map.begin(); i != tag_map.end(); ++i) { 
    VAL(glue_cast<std::string>((*i).first));
  }

  tag_map[glue_cast<UnicodeString>("Count")] = new factory<CountTag>();
  tag_map[glue_cast<UnicodeString>("EchoTag")] = new factory<EchoTag>();
  me.bindings(tag_map);

  result = me.evaluate();
  VAL(mru::glue_cast<std::string>(result));
  result = me.evaluate();
  VAL(mru::glue_cast<std::string>(result));
  result = me.evaluate();
  VAL(mru::glue_cast<std::string>(result));
  result = me.evaluate();
  VAL(mru::glue_cast<std::string>(result));
  result = me.evaluate();
  VAL(mru::glue_cast<std::string>(result));
  MSG("----------");
  //VAL(mru::glue_cast<std::string>(me.evaluate()));
  //UnicodeString result = MetatagExpression::evaluate("%Count(start=0)_file_%ToUpper(){%Name(%Nontag(\\))_ma_kota}", bindings);
  //VAL(glue_cast<std::string>(result));
  
}

void
metatag_tests::tokenizing(void)
{
  FO("metatag_tests::tokenizing(void)");
}

void
metatag_tests::empty_expression(void)
{
  MetatagExpression::parse("");
}

void
metatag_tests::unclosed_area_of_effect(void)
{
  MetatagExpression::parse("%EchoTag(){test");
}

void
metatag_tests::unclosed_arguments(void)
{
  MetatagExpression::parse("%EchoTag({test}");
}

void
metatag_tests::no_arguments(void)
{
  MetatagExpression::parse("%EchoTag{test}");
}

void
metatag_tests::space_metatag(void)
{
  MetatagExpression::parse("% EchoTag{test}");
}

void
metatag_tests::no_metatag_name(void)
{
  MetatagExpression::parse("%()");
}

void
metatag_tests::arg_start_in_text(void)
{
  MetatagExpression::parse("test ( bar");
}

void
metatag_tests::arg_end_in_text(void)
{
  MetatagExpression::parse("test ) bar");
}

void
metatag_tests::aoe_start_in_text(void)
{
  MetatagExpression::parse("test { bar");
}

void
metatag_tests::aoe_end_in_text(void)
{
  MetatagExpression::parse("test } bar");
}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(metatag_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

