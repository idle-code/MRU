#ifndef METATAG_EXPRESSION_TOKENIZER_TEST_HPP
#define METATAG_EXPRESSION_TOKENIZER_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpressionLexer.hpp"
#include "types.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpressionLexer_tests : public TestCase {
public:
  typedef MetatagExpressionLexer Lexer;
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

  void static_join(void);
  void join(void);
  void get_tokens(void);

  CPPUNIT_TEST_SUITE(MetatagExpressionLexer_tests);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
    CPPUNIT_TEST(flat_expr);
    CPPUNIT_TEST(nested_expr);
    CPPUNIT_TEST(invalid_expr);
    CPPUNIT_TEST(escaped_expr);
    CPPUNIT_TEST(double_escaped_expr);
    //CPPUNIT_TEST(escaped_normal_expr); //fix in future or implement in lexer

    CPPUNIT_TEST(static_join);
    CPPUNIT_TEST(join);
    CPPUNIT_TEST(get_tokens);
  CPPUNIT_TEST_SUITE_END();

private:
  MetatagExpressionLexer lexer;
  UnicodeString expr_str;
  Lexer::TokenList expected_tokens;
  void compare_token_lists(const Lexer::TokenList &provided_tokens);
};

#define TOKEN(VAL,TYPE) \
  { \
    Lexer::Token token; \
    token.position = expr_str.indexOf(VAL);\
    token.value = VAL; \
    token.type = Lexer::Token::TYPE;  \
    expected_tokens.push_back(token); \
  }

#define TOKENat(N,VAL,TYPE) \
  { \
    Lexer::Token token; \
    token.position = N; \
    token.value = VAL; \
    token.type = Lexer::Token::TYPE;  \
    expected_tokens.push_back(token); \
  }

#endif /* METATAG_EXPRESSION_TOKENIZER_TEST_HPP */

