#ifndef METATAG_EXPRESSION_PARSER_TESTS_HPP
#define METATAG_EXPRESSION_PARSER_TESTS_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpressionParser.hpp"
#include "types.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpressionParser_tests : public TestCase {
public:
  void setUp(void);

  void empty_expr(void);
  void static_expr(void);
  void single_expr(void);
  void single_with_args_expr(void);
  void compound_flat_expr(void);
  void simple_aoe(void);
  void nested_aoe(void);

  void no_name(void);
  void invalid_name(void);
  void missing_arg_start(void);
  void missing_arg_end(void); 
  void missing_aoe_end(void); 
  void aoe_in_text(void);
  void arg_start_in_text(void);


  CPPUNIT_TEST_SUITE(MetatagExpressionParser_tests);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
    CPPUNIT_TEST(single_expr);
    CPPUNIT_TEST(single_with_args_expr);
    CPPUNIT_TEST(compound_flat_expr);
    CPPUNIT_TEST(simple_aoe);
    CPPUNIT_TEST(nested_aoe);

    CPPUNIT_TEST_EXCEPTION(no_name, MetatagExpression::ParserException);
    CPPUNIT_TEST_EXCEPTION(invalid_name, MetatagExpression::ParserException);
    CPPUNIT_TEST_EXCEPTION(missing_arg_start, MetatagExpression::ParserException);
    CPPUNIT_TEST_EXCEPTION(missing_arg_end, MetatagExpression::ParserException);
    CPPUNIT_TEST_EXCEPTION(missing_aoe_end, MetatagExpression::ParserException);
    CPPUNIT_TEST_EXCEPTION(aoe_in_text, MetatagExpression::ParserException);
    CPPUNIT_TEST_EXCEPTION(arg_start_in_text, MetatagExpression::ParserException);
    //CPPUNIT_TEST_EXCEPTION(, MetatagExpression::ParserException);
  CPPUNIT_TEST_SUITE_END();

private:
  typedef MetatagExpression::Parser Parser;
  Parser parser;
  Parser::TagEntry::Pointer expected_expression_root;
  Parser::TagEntry::Pointer expression_root;
  UnicodeString expr_str;

  void compare_entry_trees(const Parser::TagEntry::Pointer provided_expression_root) const;
  void compare_entries(const Parser::TagEntry::Pointer expected_entry, const Parser::TagEntry::Pointer provided_entry) const;
};

#define ADD_ENTRY(POS,NAME,ARGS) \
  areaOfEffectMembers.push_back(Parser::TagEntry::Pointer(new Parser::TagEntry(POS,NAME,ARGS)))

#define LAST_ENTRY \
  areaOfEffectMembers.back()

#endif /* METATAG_EXPRESSION_PARSER_TESTS_HPP */

