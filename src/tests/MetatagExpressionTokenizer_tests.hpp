#ifndef METATAG_EXPRESSION_TOKENIZER_TEST_HPP
#define METATAG_EXPRESSION_TOKENIZER_TEST_HPP

#include "MetatagExpressionTokenizer.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;
using namespace mru;

class MetatagExpressionTokenizer_tests : public TestCase {
public:
  void setUp(void);

  void empty_expr(void);
  void static_expr(void);
  void flat_expr(void);
  void nested_expr(void);
  void invalid_expr(void);
  void escaped_expr(void);
  void double_escaped_expr(void);
  void escaped_normal_expr(void);

  CPPUNIT_TEST_SUITE(MetatagExpressionTokenizer_tests);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
    CPPUNIT_TEST(flat_expr);
    CPPUNIT_TEST(nested_expr);
    CPPUNIT_TEST(invalid_expr);
    CPPUNIT_TEST(escaped_expr);
    CPPUNIT_TEST(double_escaped_expr);
    //CPPUNIT_TEST(escaped_normal_expr); //fix in future or implement in lexer
  CPPUNIT_TEST_SUITE_END();

private:
  UnicodeString expr_str;
  std::list<UnicodeString> expected_words;
  void compare_to_expected(MetatagExpression::Tokenizer &tokenizer);
};

#define WORD(VAL) \
  expected_words.push_back(glue_cast<UnicodeString>(VAL));


#endif /* METATAG_EXPRESSION_TOKENIZER_TEST_HPP */

