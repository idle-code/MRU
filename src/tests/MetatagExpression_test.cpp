#include "UnicodeStringStreamOperator.hpp"
#include "MetatagExpression_test.hpp"
#include "glue.hpp"

void
MetatagExpression_tests::setUp(void)
{
  expr_str = UnicodeString();
}

/* ------------------------------------------------------------------------- */

void
MetatagExpression_tests::initial_state(void)
{

}

void
MetatagExpression_tests::empty_expr(void)
{
  MetatagExpression expr;

  CPPUNIT_ASSERT_EQUAL(UnicodeString(), expr.text());
}

void
MetatagExpression_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text()");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::nested_expr(void)
{
  expr_str = glue_cast<UnicodeString>(" Text with spaces % And Token Name (in argument list) asdf {yet%Another(   ) token }.ext");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::invalid_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%}(2\\1%}){");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %there");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("_\\\\_");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT(expr.isValid());
  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT(expr.isValid());
  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}


void
MetatagExpression_tests::static_expr_evaluation(void)
{

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

