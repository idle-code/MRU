#include "UnicodeStringStreamOperator.hpp"
#include "MetatagExpressionTokenizer_tests.hpp"
#include "glue.hpp"

void
MetatagExpressionTokenizer_tests::setUp(void)
{
  expected_words.clear();
  expr_str = UnicodeString();
  tokenizer = MetatagExpressionTokenizer();
}

void
MetatagExpressionTokenizer_tests::compare_word_lists(const MetatagExpressionTokenizer::WordList &provided_words)
{
  MetatagExpressionTokenizer::WordList::const_iterator eti = expected_words.begin();
  MetatagExpressionTokenizer::WordList::const_iterator ti = provided_words.begin();

  for(; eti != expected_words.end() && ti != provided_words.end(); ++eti, ++ti) {
    //std::cout << "'" << *eti << "' == '" << *ti << "'" << std::endl;
    CPPUNIT_ASSERT_EQUAL(*eti, *ti);
  }

  CPPUNIT_ASSERT(eti == expected_words.end());
  CPPUNIT_ASSERT(ti == provided_words.end());
}

/* ------------------------------------------------------------------------- */

void
MetatagExpressionTokenizer_tests::empty_expr(void)
{
  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(UnicodeString());

  CPPUNIT_ASSERT(0 == words.size()); 
  compare_word_lists(words);
}

void
MetatagExpressionTokenizer_tests::static_expr(void)
{
  expr_str = glue_cast<UnicodeString>("Text");
  
  WORD("Text");

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
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

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
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

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
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

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
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

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

void
MetatagExpressionTokenizer_tests::double_escaped_expr(void)
{
  expr_str = glue_cast<UnicodeString>("a\\\\b");

  WORD("a");
  WORD("\\");
  WORD("\\b");

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

void
MetatagExpressionTokenizer_tests::escaped_normal_expr(void)
{
  expr_str = glue_cast<UnicodeString>("foo\\bar");

  WORD("foo\\bar");

  const MetatagExpressionTokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
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

