#include "MetatagExpressionTokenizer_tests.hpp"

void
MetatagExpressionTokenizer_tests::setUp(void)
{
  expr_str = UnicodeString();
  expected_words.clear();
}

void
MetatagExpressionTokenizer_tests::compare_to_expected(Metatag::Tokenizer &tokenizer)
{
  std::list<UnicodeString>::const_iterator eti = expected_words.begin();
  for(; eti != expected_words.end() && !tokenizer.atEnd(); ++eti) {
    UnicodeString word = tokenizer.getCurrent();
    //std::cout << "'" << *eti << "' == '" << word << "'" << std::endl;
    CPPUNIT_ASSERT_EQUAL(*eti, word);
    tokenizer.next();
  }
  CPPUNIT_ASSERT(eti == expected_words.end());
  CPPUNIT_ASSERT(tokenizer.atEnd());
}

/* ------------------------------------------------------------------------- */

void
MetatagExpressionTokenizer_tests::empty_expr(void)
{
  Metatag::Tokenizer tokenizer((UnicodeString()));

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");
  
  WORD("Text");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::flat_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%Text(){}");

  WORD("%");
  WORD("Text");
  WORD("(");
  WORD(")");
  WORD("{");
  WORD("}");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::nested_expr(void)
{
  expr_str = glue_cast<UnicodeString>(" Text with spaces % And Token Name (in argument list) asdf {yet%Another(   ) word }.ext");

  WORD(" Text with spaces ");
  WORD("%");
  WORD(" And Token Name ");
  WORD("(");
  WORD("in argument list");
  WORD(")");
  WORD(" asdf ");
  WORD("{");
  WORD("yet");
  WORD("%");
  WORD("Another");
  WORD("(");
  WORD("   ");
  WORD(")");
  WORD(" word ");
  WORD("}");
  WORD(".ext");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::invalid_expr(void)
{
  expr_str = glue_cast<UnicodeString>("%}(21%}){");

  WORD("%");
  WORD("}");
  WORD("(");
  WORD("21");
  WORD("%");
  WORD("}");
  WORD(")");
  WORD("{");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Some\\(text\\) here, but not %there");

  WORD("Some");
  WORD("\\");
  WORD("(text");
  WORD("\\");
  WORD(") here, but not ");
  WORD("%");
  WORD("there");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("a\\\\b");

  WORD("a");
  WORD("\\");
  WORD("\\b");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

void
MetatagExpressionTokenizer_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  WORD("foo\\bar");

  Metatag::Tokenizer tokenizer(expr_str);

  compare_to_expected(tokenizer);
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MetatagExpressionTokenizer_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

