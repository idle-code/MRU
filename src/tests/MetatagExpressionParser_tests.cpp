#include "glue.hpp"
using mru::operator<<;
#include "MetatagExpressionParser_tests.hpp"

void
MetatagExpressionParser_tests::setUp(void)
{
  expr_str = UnicodeString();
  //parser = MetatagExpressionParser();
  expected_expression_root.reset();
  expected_expression_root = Parser::TagEntry::Pointer(new Parser::TagEntry(-1, "", ""));
  expression_root.reset();
}

void
MetatagExpressionParser_tests::compare_entry_trees(const Parser::TagEntry::Pointer provided_expression_root) const
{
  compare_entries(expected_expression_root, provided_expression_root); 
}

void
print_entry_tree(const mru::MetatagExpression::Parser::TagEntry::Pointer root)
{
  MSG("name '" << root->name << "' args: '" << root->arguments << "' {");
  mru::MetatagExpression::Parser::TagEntry::MemberList::const_iterator ei = root->areaOfEffectMembers.begin(); 
  mru::MetatagExpression::Parser::TagEntry::MemberList::const_iterator ei_end = root->areaOfEffectMembers.end(); 
  LEV_UP
  for(; ei != ei_end; ++ei) {
    print_entry_tree(*ei);
  }
  LEV_DOWN
  MSG("}");
}

void
MetatagExpressionParser_tests::compare_entries(const Parser::TagEntry::Pointer expected_entry, const Parser::TagEntry::Pointer provided_entry) const
{
  CPPUNIT_ASSERT(bool(expected_entry));
  CPPUNIT_ASSERT(bool(provided_entry));

  //CPPUNIT_ASSERT_EQUAL(expected_entry->position, provided_entry->position);
  CPPUNIT_ASSERT_EQUAL(expected_entry->name, provided_entry->name);
  CPPUNIT_ASSERT_EQUAL(expected_entry->arguments, provided_entry->arguments);
  CPPUNIT_ASSERT_EQUAL(expected_entry->haveAreaOfEffectMembers(), provided_entry->haveAreaOfEffectMembers());

  CPPUNIT_ASSERT_EQUAL(expected_entry->areaOfEffectMembers.size(), provided_entry->areaOfEffectMembers.size());

  Parser::TagEntry::MemberList::const_iterator ei = expected_entry->areaOfEffectMembers.begin(); 
  Parser::TagEntry::MemberList::const_iterator ei_end = expected_entry->areaOfEffectMembers.end(); 
  Parser::TagEntry::MemberList::const_iterator pi = provided_entry->areaOfEffectMembers.begin(); 
  Parser::TagEntry::MemberList::const_iterator pi_end = provided_entry->areaOfEffectMembers.end(); 
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
MetatagExpressionParser_tests::single_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%MetatagName()");

  expected_expression_root->ADD_ENTRY(0, "MetatagName", "");

  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::single_with_args_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%MetatagName( and arguments )");

  expected_expression_root->ADD_ENTRY(0, "MetatagName", " and arguments ");

  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::compound_flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Casual Text %Tag() followed by text %AndOther(tag).ext");

  expected_expression_root->ADD_ENTRY(0, "", "Casual Text ");
  expected_expression_root->ADD_ENTRY(0, "Tag", "");
  expected_expression_root->ADD_ENTRY(0, "", " followed by text ");
  expected_expression_root->ADD_ENTRY(0, "AndOther", "tag");
  expected_expression_root->ADD_ENTRY(0, "", ".ext");

  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::simple_aoe(void)
{
  expr_str = glue_cast<UnicodeString>("%Tag(){Text}");

  expected_expression_root->ADD_ENTRY(0, "Tag", "");
  expected_expression_root->LAST_ENTRY->ADD_ENTRY(0, "", "Text");

  expression_root = parser.parse(expr_str);

  compare_entry_trees(expression_root);
}

void
MetatagExpressionParser_tests::nested_aoe(void)
{
  expr_str = glue_cast<UnicodeString>("%Tag1(arg){Some Text%Tag2() after tag}---%Tag3(){}");

  expected_expression_root->ADD_ENTRY(0, "Tag1", "arg");
  expected_expression_root->LAST_ENTRY->ADD_ENTRY(0, "", "Some Text");
  expected_expression_root->LAST_ENTRY->ADD_ENTRY(0, "Tag2", "");
  expected_expression_root->LAST_ENTRY->ADD_ENTRY(0, "", " after tag");
  expected_expression_root->ADD_ENTRY(0, "", "---");
  expected_expression_root->ADD_ENTRY(0, "Tag3", "");

  expression_root = parser.parse(expr_str);

  //MSG("Expected:");
  //print_entry_tree(expected_expression_root);
  //MSG("Provided:");
  //print_entry_tree(expression_root);

  compare_entry_trees(expression_root);
}

/* ------------------------------------------------------------------------- */

void
MetatagExpressionParser_tests::no_name(void)
{
  expr_str = glue_cast<UnicodeString>("%");

  expression_root = parser.parse(expr_str); //throw
}

void
MetatagExpressionParser_tests::invalid_name(void)
{
  expr_str = glue_cast<UnicodeString>("%(()");

  expression_root = parser.parse(expr_str); //throw
}

void
MetatagExpressionParser_tests::missing_arg_start(void)
{
  expr_str = glue_cast<UnicodeString>("%Tag");

  expression_root = parser.parse(expr_str); //throw
}

void
MetatagExpressionParser_tests::missing_arg_end(void)
{
  expr_str = glue_cast<UnicodeString>("%Tag(");

  expression_root = parser.parse(expr_str); //throw
}

void
MetatagExpressionParser_tests::missing_aoe_end(void)
{
  expr_str = glue_cast<UnicodeString>("%Tag(){");

  expression_root = parser.parse(expr_str); //throw
}

void
MetatagExpressionParser_tests::aoe_in_text(void)
{
  expr_str = glue_cast<UnicodeString>("}");

  expression_root = parser.parse(expr_str); //throw
}

void
MetatagExpressionParser_tests::arg_start_in_text(void)
{
  expr_str = glue_cast<UnicodeString>("(");

  expression_root = parser.parse(expr_str); //throw
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

