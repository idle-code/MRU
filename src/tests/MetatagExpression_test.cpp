#include "MetatagExpression_test.hpp"
#include "glue.hpp"

void
MetatagExpression_tests::initial_state(void)
{

}

void
MetatagExpression_tests::empty_expr(void)
{
  MetatagExpression expr;

  CPPUNIT_ASSERT(UnicodeString() == expr.text());
}

void
MetatagExpression_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT(expr.isValid());
  CPPUNIT_ASSERT(expr_str == expr.text());
}

void
MetatagExpression_tests::static_expr_evaluation(void)
{

}

void
MetatagExpression_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text()");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT(expr.isValid());
  CPPUNIT_ASSERT(expr_str == expr.text());
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

