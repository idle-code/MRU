#include "UnicodeStringStreamOperator.hpp"
#include "MetatagExpressionParser_tests.hpp"
#include "glue.hpp"

void
MetatagExpressionParser_tests::setUp(void)
{
  expr_str = UnicodeString();
  //parser = MetatagExpressionParser();
  expected_expression_root.reset();
  expected_expression_root = Parser::Entry::Pointer(new Parser::Entry(-1, "", ""));
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
  CPPUNIT_ASSERT(bool(expected_entry));
  CPPUNIT_ASSERT(bool(provided_entry));

  CPPUNIT_ASSERT_EQUAL(expected_entry->position, provided_entry->position);
  CPPUNIT_ASSERT_EQUAL(expected_entry->name, provided_entry->name);
  CPPUNIT_ASSERT_EQUAL(expected_entry->arguments, provided_entry->arguments);
  CPPUNIT_ASSERT_EQUAL(expected_entry->isAreaOfEffectMembersPresent(), provided_entry->isAreaOfEffectMembersPresent());

  CPPUNIT_ASSERT_EQUAL(expected_entry->areaOfEffectMembers.size(), provided_entry->areaOfEffectMembers.size());

  Parser::Entry::MemberList::const_iterator ei = expected_entry->areaOfEffectMembers.begin(); 
  Parser::Entry::MemberList::const_iterator ei_end = expected_entry->areaOfEffectMembers.end(); 
  Parser::Entry::MemberList::const_iterator pi = provided_entry->areaOfEffectMembers.begin(); 
  Parser::Entry::MemberList::const_iterator pi_end = provided_entry->areaOfEffectMembers.end(); 
  for(; ei != ei_end && pi != pi_end; ++ei, ++pi) {
    compare_entries(*ei, *pi);
  }
  CPPUNIT_ASSERT(ei == ei_end);
  CPPUNIT_ASSERT(pi == pi_end);
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
  
  expected_expression_root->ADD_ENTRY(0, "", "Text");

  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(");

  expected_expression_root->ADD_ENTRY(0, "Text", "");

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

