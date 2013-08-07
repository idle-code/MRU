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
MetatagExpressionLexer_tests::tearDown(void)
{
  Lexer lexer(boost::make_shared<Tokenizer>(expr_str));

  compare_to_expected(lexer);
}

void
MetatagExpressionLexer_tests::compare_to_expected(MetatagExpression::Lexer &lexer)
{
  std::list<MetatagExpression::Token>::const_iterator eti = expected_tokens.begin();
  for(; eti != expected_tokens.end() && !lexer.atEnd(); ++eti) {
    //std::cout << eti->value << " == " << lexer.getCurrent().value << std::endl;
    CPPUNIT_ASSERT_EQUAL(eti->value, lexer.getCurrent().value);
    //std::cout << eti->position << " == " << lexer.getCurrent().position << std::endl;
    CPPUNIT_ASSERT_EQUAL(eti->position, lexer.getCurrent().position);
    CPPUNIT_ASSERT(eti->type == lexer.getCurrent().type);
    lexer.next();
  }

  CPPUNIT_ASSERT(eti == expected_tokens.end());
  CPPUNIT_ASSERT(lexer.atEnd());
}

/* ------------------------------------------------------------------------- */

void
MetatagExpressionLexer_tests::empty_expr(void)
{
  expr_str = UnicodeString();
}

void
MetatagExpressionLexer_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");
  
  TOKEN("Text", Text);
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
}

void
MetatagExpressionLexer_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("a\\\\b");

  TOKEN("a", Text);
  TOKEN("\\", EscapeSequence);
  TOKEN("\\b", Text);
}

void
MetatagExpressionLexer_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  TOKEN("foo\\bar", Text);
}

/* ------------------------------------------------------------------------- */

MetatagExpressionLexer_tests::ValueList
MetatagExpressionLexer_tests::getSampleValues(void)
{
  expr_str.remove();
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  expected_tokens.clear();
  TOKEN("%", MetatagStart);
  TOKEN("Text", Text);
  TOKEN("(", ArgumentListStart);
  TOKEN(")", ArgumentListEnd);
  TOKEN("{", AreaOfEffectStart);
  TOKEN("}", AreaOfEffectEnd);
  
  return expected_tokens;
}

mru::ConstIterator<MetatagExpression::Token>::Pointer
MetatagExpressionLexer_tests::getConstIterator(const ValueList &values_in_container)
{
  expr_str.remove();
  for(ValueList::const_iterator i = values_in_container.begin(); i != values_in_container.end(); ++i) {
    expr_str += i->value;
  }

  return boost::make_shared<Lexer>(boost::make_shared<Tokenizer>(expr_str));
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MetatagExpressionLexer_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */


