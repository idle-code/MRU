#include "UnicodeStringStreamOperator.hpp"
#include "MetatagExpressionLexer_tests.hpp"
#include "glue.hpp"
#include <boost/make_shared.hpp>

void
MetatagExpressionLexer_tests::setUp(void)
{
  expected_tokens.clear();
  expr_str = UnicodeString();
}

void
MetatagExpressionLexer_tests::compare_to_expected(MetatagExpression::Lexer &lexer)
{
  std::list<MetatagExpression::Token>::const_iterator eti = expected_tokens.begin();
  for(; eti != expected_tokens.end() && !lexer.atEnd(); ++eti) {
    //std::cout << eti->value << " == " << ti->value << std::endl;
    
    CPPUNIT_ASSERT_EQUAL(eti->value, lexer.getCurrent().value);
    CPPUNIT_ASSERT_EQUAL(eti->position, lexer.getCurrent().position);
    CPPUNIT_ASSERT(eti->type == lexer.getCurrent().type);
  }

  CPPUNIT_ASSERT(eti == expected_tokens.end());
  CPPUNIT_ASSERT(lexer.atEnd());
}

/* ------------------------------------------------------------------------- */

void
MetatagExpressionLexer_tests::empty_expr(void)
{
  expr_str = UnicodeString();
  Lexer lexer(boost::make_shared<Tokenizer>(expr_str));

  compare_to_expected(lexer);
}
#if 0
void
MetatagExpressionLexer_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");
  
  TOKEN("Text", Text);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  TOKEN("%", MetatagStart);
  TOKEN("Text", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("}", AreaOfEffectEnd);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::nested_expr(void)
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
  TOKENat(63, "%", MetatagStart);
  TOKEN("Another", Text);
  TOKENat(71, "(", ArgumentListStart);
  TOKEN("   ", Text);
  TOKENat(75, ")", ArgumentListEnd);
  TOKEN(" token ", Text);
  TOKEN("}", AreaOfEffectEnd);
  TOKEN(".ext", Text);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::invalid_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%}(21%}){");

  TOKEN("%", MetatagStart);
  TOKEN("}", AreaOfEffectEnd);
  TOKEN("(", ArgumentListStart);
  TOKEN("21", Text);
  TOKENat(5, "%", MetatagStart);
  TOKENat(6, "}", AreaOfEffectEnd);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %there");

  TOKEN("Some", Text);
  TOKEN("\\", EscapeSequence);
  TOKEN("(text", Text);
  TOKENat(10, "\\", EscapeSequence);
  TOKEN(") here, but not ", Text);
  TOKEN("%", MetatagStart);
  TOKEN("there", Text);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("a\\\\b");

  TOKEN("a", Text);
  TOKEN("\\", EscapeSequence);
  TOKEN("\\b", Text);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  TOKEN("foo\\bar", Text);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  compare_token_lists(tokens);
}

void
MetatagExpressionLexer_tests::static_join(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  TOKEN("%", MetatagStart);
  TOKEN("Text", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("}", AreaOfEffectEnd);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, MetatagExpressionLexer::joinTokens(tokens));
}

void
MetatagExpressionLexer_tests::join(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  TOKEN("%", MetatagStart);
  TOKEN("Text", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("}", AreaOfEffectEnd);

  lexer.analyze(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, lexer.joinTokens());
}

void
MetatagExpressionLexer_tests::get_tokens(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  TOKEN("%", MetatagStart);
  TOKEN("Text", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("}", AreaOfEffectEnd);

  const MetatagExpressionLexer::TokenList &tokens = lexer.analyze(expr_str);

  expected_tokens = tokens;

  compare_token_lists(tokens);
}
#endif

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MetatagExpressionLexer_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */


