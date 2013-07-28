#ifndef METATAG_EXPRESSION_TOKENIZER_TEST_HPP
#define METATAG_EXPRESSION_TOKENIZER_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpression.hpp"
#include "types.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpressionTokenizer_tests : public TestCase {
private:
  std::list<MetatagExpression::Tokenizer::Token> expected_tokens;
  MetatagExpression::Tokenizer tokenizer;
  UnicodeString expr_str;
public:
  void setUp(void);

  void compare_token_lists(const std::list<MetatagExpression::Tokenizer::Token> &expected_tokens, const std::list<MetatagExpression::Tokenizer::Token> &provided_tokens) const;

  void empty_expr(void);
  void static_expr(void);
  void flat_expr(void);
  void nested_expr(void);
  void invalid_expr(void);
  void escaped_expr_full(void);
  void double_escaped_expr_full(void);
  void escaped_normal_expr_full(void);

  CPPUNIT_TEST_SUITE(MetatagExpressionTokenizer_tests);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
    CPPUNIT_TEST(flat_expr);
    CPPUNIT_TEST(nested_expr);
    CPPUNIT_TEST(invalid_expr);
    //CPPUNIT_TEST(escaped_expr);
    CPPUNIT_TEST(escaped_expr_full);
    CPPUNIT_TEST(double_escaped_expr_full);
    CPPUNIT_TEST(escaped_normal_expr_full);
  CPPUNIT_TEST_SUITE_END();
};


#endif /* METATAG_EXPRESSION_TOKENIZER_TEST_HPP */

