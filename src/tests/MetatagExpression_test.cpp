#include "UnicodeStringStreamOperator.hpp"
#include "MetatagExpression_test.hpp"
#include "glue.hpp"

void
MetatagExpression_tests::setUp(void)
{
  expr_str = UnicodeString();
  expected_tokens.clear();
}

/* ------------------------------------------------------------------------- */

void
MetatagExpression_tests::empty_expr_tokenization(void)
{
  MetatagExpression expr;

  std::list<MetatagExpression::Token> tokens = expr.tokenize(UnicodeString());

  CPPUNIT_ASSERT_EQUAL(0ul, tokens.size()); 
}

void
MetatagExpression_tests::static_expr_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("Text");
  MetatagExpression expr;

  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  CPPUNIT_ASSERT_EQUAL(1ul, tokens.size()); 

  CPPUNIT_ASSERT_EQUAL(expr_str, tokens.front().value);
  CPPUNIT_ASSERT_EQUAL(0, tokens.front().position);
  CPPUNIT_ASSERT_EQUAL(MetatagExpression::Token::Text, tokens.front().type);
}


void
MetatagExpression_tests::compare_token_lists(const std::list<MetatagExpression::Token> &expected_tokens, const std::list<MetatagExpression::Token> &provided_tokens) const
{
  std::list<MetatagExpression::Token>::const_iterator eti = expected_tokens.begin();
  std::list<MetatagExpression::Token>::const_iterator ti = provided_tokens.begin();
  std::list<MetatagExpression::Token>::const_iterator eti_end = expected_tokens.end();
  std::list<MetatagExpression::Token>::const_iterator ti_end = provided_tokens.end();

  CPPUNIT_ASSERT(ti_end != ti);
  CPPUNIT_ASSERT(eti_end != eti);

  for(; ti != ti_end && eti != eti_end; ++ti, ++eti) {
    //std::cout << "---------------------" << std::endl;
    //std::cout << (*eti).value << " == " << (*ti).value << std::endl;
    //std::cout << (*eti).position << " == " << (*ti).position << std::endl;
    CPPUNIT_ASSERT_EQUAL((*eti).value, (*ti).value);
    CPPUNIT_ASSERT_EQUAL((*eti).position, (*ti).position);
    CPPUNIT_ASSERT((*eti).type == (*ti).type);
  }

  CPPUNIT_ASSERT(ti_end == ti);
  CPPUNIT_ASSERT(eti_end == eti);
}

#define TOKEN(VAL,TYPE) \
  expected_tokens.push_back(MetatagExpression::Token(expr_str.indexOf(glue_cast<UnicodeString>(VAL)), glue_cast<UnicodeString>(VAL), MetatagExpression::Token::TYPE))

#define TOKENn(POS,VAL,TYPE) \
  expected_tokens.push_back(MetatagExpression::Token(POS, glue_cast<UnicodeString>(VAL), MetatagExpression::Token::TYPE))

void
MetatagExpression_tests::flat_expr_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  TOKEN("%", MetatagStart);
  TOKEN("Text", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("}", AreaOfEffectEnd);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

void
MetatagExpression_tests::nested_expr_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>(" Text with spaces % And Token Name (in argument list) asdf {yet%Another(   ) token }.ext");

  TOKEN(" Text with spaces ", Text);
  TOKEN("%", MetatagStart);
  TOKEN(" And Token Name ", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN("in argument list", Text);
  TOKEN(")", ArgumentListEnd);
  TOKEN(" asdf ", Text);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("yet", Text);
  TOKENn(63, "%", MetatagStart);
  TOKEN("Another", Text);
  TOKENn(71, "(", ArgumentListStart);
  TOKEN("   ", Text);
  TOKENn(75, ")", ArgumentListEnd);
  TOKEN(" token ", Text);
  TOKEN("}", AreaOfEffectEnd);
  TOKEN(".ext", Text);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

void
MetatagExpression_tests::invalid_expr_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("%}(21%}){");

  TOKEN("%", MetatagStart);
  TOKEN("}", AreaOfEffectEnd);
  TOKEN("(", ArgumentListStart);
  TOKEN("21", Text);
  TOKENn(5, "%", MetatagStart);
  TOKENn(6, "}", AreaOfEffectEnd);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

void
MetatagExpression_tests::escaped_expr_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %there");

  TOKENn(0,"Some(text) here, but not ", Text);
  TOKENn(25, "%", MetatagStart);
  TOKENn(26, "there", Text);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

void
MetatagExpression_tests::escaped_expr_full_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %there");

  TOKEN("Some", Text);
  TOKEN("\\", EscapeSequence);
  TOKEN("(text", Text);
  TOKENn(10, "\\", EscapeSequence);
  TOKEN(") here, but not ", Text);
  TOKEN("%", MetatagStart);
  TOKEN("there", Text);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

void
MetatagExpression_tests::double_escaped_expr_full_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("a\\\\b");

  TOKEN("a", Text);
  TOKEN("\\", EscapeSequence);
  TOKEN("\\b", Text);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

void
MetatagExpression_tests::escaped_normal_expr_full_tokenization(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  TOKEN("foo\\bar", Text);

  MetatagExpression expr;
  std::list<MetatagExpression::Token> tokens = expr.tokenize(expr_str);

  compare_token_lists(expected_tokens, tokens);
}

/* ------------------------------------------------------------------------- */

void
MetatagExpression_tests::initial_state(void)
{

}

void
MetatagExpression_tests::empty_expr(void)
{
  MetatagExpression expr;

  CPPUNIT_ASSERT_EQUAL(UnicodeString(), expr.text());
}

void
MetatagExpression_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text()");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::nested_expr(void)
{
  expr_str = glue_cast<UnicodeString>(" Text with spaces % And Token Name (in argument list) asdf {yet%Another(   ) token }.ext");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::invalid_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%}(2\\1%}){");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %there");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("_\\\\_");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT(expr.isValid());
  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}

void
MetatagExpression_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  MetatagExpression expr(expr_str);

  CPPUNIT_ASSERT(expr.isValid());
  CPPUNIT_ASSERT_EQUAL(expr_str, expr.text());
}


void
MetatagExpression_tests::static_expr_evaluation(void)
{

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

