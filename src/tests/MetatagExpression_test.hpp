#ifndef METATAG_EXPRESSION_TEST_HPP
#define METATAG_EXPRESSION_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpression.hpp"
#include "types.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpression_tests : public TestCase {
public:
  UnicodeString expr_str;
  std::list<MetatagExpression::Token> expected_tokens;
  void setUp(void);
public:
  void compare_token_lists(const std::list<MetatagExpression::Token> &expected_tokens, const std::list<MetatagExpression::Token> &provided_tokens) const;

  void empty_expr_tokenization(void);
  void static_expr_tokenization(void);
  void flat_expr_tokenization(void);
  void nested_expr_tokenization(void);
  void invalid_expr_tokenization(void);
  void escaped_expr_tokenization(void); //TODO remove
  void escaped_expr_full_tokenization(void);
  void double_escaped_expr_full_tokenization(void);
  void escaped_normal_expr_full_tokenization(void);

  void initial_state(void);
  void empty_expr(void);
  void static_expr(void);
  void flat_expr(void);
  void nested_expr(void);
  void invalid_expr(void);
  void escaped_expr(void);
  void double_escaped_expr(void);
  void escaped_normal_expr(void);

  void static_expr_evaluation(void);


  CPPUNIT_TEST_SUITE(MetatagExpression_tests);
    CPPUNIT_TEST(empty_expr_tokenization);
    CPPUNIT_TEST(static_expr_tokenization);
    CPPUNIT_TEST(flat_expr_tokenization);
    CPPUNIT_TEST(nested_expr_tokenization);
    CPPUNIT_TEST(invalid_expr_tokenization);
    //CPPUNIT_TEST(escaped_expr_tokenization);
    CPPUNIT_TEST(escaped_expr_full_tokenization);
    CPPUNIT_TEST(double_escaped_expr_full_tokenization);
    CPPUNIT_TEST(escaped_normal_expr_full_tokenization);

    CPPUNIT_TEST(initial_state);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
    CPPUNIT_TEST(flat_expr);
    CPPUNIT_TEST(nested_expr);
    CPPUNIT_TEST(invalid_expr);
    CPPUNIT_TEST(escaped_expr);
    CPPUNIT_TEST(double_escaped_expr);
    CPPUNIT_TEST(escaped_normal_expr);
    //CPPUNIT_TEST(static_expr_evaluation);
    //CPPUNIT_TEST(flat_expr);
  CPPUNIT_TEST_SUITE_END();
};


#endif /* METATAG_EXPRESSION_TEST_HPP */

