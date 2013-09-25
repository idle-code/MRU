#include "glue.hpp"
using mru::operator<<;
#include "MetatagExpression_tests.hpp"
#include "MockFileIterator.hpp"

MetatagExpression_tests::MetatagExpression_tests(void)
{
  file_list.push_back("a");
  file_list.push_back("b");
  file_list.push_back("c");
}

void
MetatagExpression_tests::setUp(void)
{
  expr_str = UnicodeString();
  expr.reset();
  file_iterator = boost::make_shared<MockFileIterator>(file_list);
  CPPUNIT_ASSERT(file_iterator);
}

/* ------------------------------------------------------------------------- */

void
MetatagExpression_tests::empty_expr(void)
{
  expr = Metatag::Expression::parse(UnicodeString());
  CPPUNIT_ASSERT(expr);
  CPPUNIT_ASSERT_EQUAL(UnicodeString(), expr->evaluate(file_iterator));
}

void
MetatagExpression_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");

  expr = Metatag::Expression::parse(expr_str);
  CPPUNIT_ASSERT(expr);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr->evaluate(file_iterator));
}

class TestMetatag : public Metatag::MetatagBase {
public:
  typedef boost::shared_ptr<TestMetatag> Pointer;
  class Factory : public MetatagBase::Factory {
  public:
    MetatagBase::Pointer
    create(void)
    {
      return boost::make_shared<TestMetatag>();
    }
  };
  friend class Factory;
public:
  TestMetatag(void) { }

  void
  initialize(const UnicodeString &arguments)
  {
    this->arguments = "[" + arguments + "]"; 
  }

  UnicodeString
  execute(const FileIterator::Pointer file_iterator , const UnicodeString &area_of_effect)
  {
    return arguments + "<" + area_of_effect + ">";
  }
public:
  UnicodeString arguments;
};

void
MetatagExpression_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Tag()");

  expr = Metatag::Expression::parse(expr_str);
  CPPUNIT_ASSERT(expr);

  Metatag::Expression::FactoryMap factory_map;
  factory_map.insert(std::make_pair("Tag", boost::make_shared<TestMetatag::Factory>()));
  expr->bindFactoryMap(factory_map);

  CPPUNIT_ASSERT_EQUAL(glue_cast<UnicodeString>("[]<>"), expr->evaluate(file_iterator));
}

void
MetatagExpression_tests::nested_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text with spaces %Tag(){yet another %Tag(   ) token }.ext");

  expr = Metatag::Expression::parse(expr_str);
  CPPUNIT_ASSERT(expr);

  Metatag::Expression::FactoryMap factory_map;
  factory_map.insert(std::make_pair("Tag", boost::make_shared<TestMetatag::Factory>()));
  expr->bindFactoryMap(factory_map);

  CPPUNIT_ASSERT_EQUAL(glue_cast<UnicodeString>("Text with spaces []<yet another [   ]<> token >.ext"), expr->evaluate(file_iterator));
}

void
MetatagExpression_tests::invalid_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%}(2\\1%}){");

  Metatag::Expression::parse(expr_str); // throw
}

void
MetatagExpression_tests::escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %Tag(there)");

  expr = Metatag::Expression::parse(expr_str);
  CPPUNIT_ASSERT(expr);

  Metatag::Expression::FactoryMap factory_map;
  factory_map.insert(std::make_pair("Tag", boost::make_shared<TestMetatag::Factory>()));
  expr->bindFactoryMap(factory_map);

  CPPUNIT_ASSERT_EQUAL(glue_cast<UnicodeString>("Some(text) here, but not [there]<>"), expr->evaluate(file_iterator));
}

void
MetatagExpression_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("_\\\\_");

  Metatag::Expression::Pointer expr = Metatag::Expression::parse(expr_str);
  CPPUNIT_ASSERT(expr != NULL);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr->text());
}

void
MetatagExpression_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  Metatag::Expression::Pointer expr = Metatag::Expression::parse(expr_str);
  CPPUNIT_ASSERT(expr != NULL);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr->text());
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MetatagExpression_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

