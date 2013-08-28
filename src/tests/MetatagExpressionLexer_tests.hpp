#ifndef METATAG_EXPRESSION_TOKENIZER_TEST_HPP
#define METATAG_EXPRESSION_TOKENIZER_TEST_HPP

#include "Metatag/Lexer.hpp"
#include "ConstIterator_tests.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;
using namespace mru;

class MetatagExpressionLexer_tests : public ConstIterator_tests<Metatag::Token> {
public:
  typedef ConstIterator_tests<Metatag::Token> Parent;
  typedef Metatag::Lexer Lexer;
  typedef Metatag::Tokenizer Tokenizer;
public:

  void setUp(void);
  void tearDown(void);

  void empty_expr(void);
  void static_expr(void);
  void flat_expr(void);
  void nested_expr(void);
  void invalid_expr(void);
  void escaped_expr(void);
  void double_escaped_expr(void);
  void escaped_normal_expr(void);

  ValueList getSampleValues(void);
  mru::ConstIterator<Metatag::Token>::Pointer getConstIterator(const ValueList &values_in_container);

  CPPUNIT_TEST_SUB_SUITE(MetatagExpressionLexer_tests, Parent);
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
  std::list<Metatag::Token> expected_tokens;
  void compare_to_expected(Metatag::Lexer &lexer);
};

#define TOKEN(VAL,TYPE) \
  { \
    Metatag::Token token; \
    token.position = expr_str.indexOf(VAL);\
    token.value = VAL; \
    token.type = Metatag::Token::TYPE;  \
    expected_tokens.push_back(token); \
  }

#define TOKENat(N,VAL,TYPE) \
  { \
    Metatag::Token token; \
    token.position = N; \
    token.value = VAL; \
    token.type = Metatag::Token::TYPE;  \
    expected_tokens.push_back(token); \
  }

#endif /* METATAG_EXPRESSION_TOKENIZER_TEST_HPP */

