#include "UnicodeStringStreamOperator.hpp"
#include "MetatagExpressionParser_tests.hpp"
#include "glue.hpp"

void
MetatagExpressionParser_tests::setUp(void)
{
  expr_str = UnicodeString();
  parser = MetatagExpressionParser();
  expected_expression_root.reset();
  expression_root.reset();
}

void
MetatagExpressionParser_tests::compare_entry_trees(const Parser::Entry::Pointer provided_expression_root) const
{
  compare_entries(expected_expression_root, provided_expression_root); 
}

void
MetatagExpressionParser_tests::compare_entries(const Parser::Entry::Pointer expected_entry, const Parser::Entry::Pointer provided_entry) const
{
  CPPUNIT_ASSERT_EQUAL(bool(expected_entry), bool(provided_entry));
  
}

/* ------------------------------------------------------------------------- */

void
MetatagExpressionParser_tests::empty_expr(void)
{
  expr_str = UnicodeString();
  
  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");
  

  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");


  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::nested_expr(void)
{
  expr_str = glue_cast<UnicodeString>(" Text with spaces % And Token Name (in argument list) asdf {yet%Another(   ) word }.ext");


  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MetatagExpressionParser_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

