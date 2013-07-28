#include "UnicodeStringStreamOperator.hpp"
#include "Tokenizer_tests.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>
#include "glue.hpp"

void
Tokenizer_tests::setUp(void)
{
  expr_str = UnicodeString();
  expected_words.clear();
}

void
Tokenizer_tests::compare_word_lists(const Tokenizer::WordList &provided_words)
{
  Tokenizer::WordList::const_iterator eti = expected_words.begin();
  Tokenizer::WordList::const_iterator ti = provided_words.begin();

  for(; eti != expected_words.end() && ti != provided_words.end(); ++eti, ++ti) {
    //std::cout << "'" << *eti << "' == '" << *ti << "'" << std::endl;
    CPPUNIT_ASSERT_EQUAL(*eti, *ti);
  }

  CPPUNIT_ASSERT(eti == expected_words.end());
  CPPUNIT_ASSERT(ti == provided_words.end());
}

/* ------------------------------------------------------------------------- */

class NotSplitingTokenizer : public mru::Tokenizer {
public:
  ActionKind
  actionOn(UChar current_character)
  {
    return Continue;
  }
};

void
Tokenizer_tests::no_split(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");

  WORD("ab|cd");

  NotSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class LeftSplitingTokenizer : public mru::Tokenizer {
public:
  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitLeft;
    return Continue;
  }
};

void
Tokenizer_tests::split_left(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");

  WORD("ab");
  WORD("|cd");

  LeftSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class RightSplitingTokenizer : public mru::Tokenizer {
public:
  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitRight;
    return Continue;
  }
};

void
Tokenizer_tests::split_right(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");

  WORD("ab|");
  WORD("cd");

  RightSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class BothSplitingTokenizer : public mru::Tokenizer {
public:
  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitBoth;
    return Continue;
  }
};

void
Tokenizer_tests::split_both(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");

  WORD("ab");
  WORD("|");
  WORD("cd");

  BothSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class SpaceStripingTokenizer : public mru::Tokenizer {
public:
  ActionKind
  actionOn(UChar current_character)
  {
    if (u_isWhitespace(current_character))
      return SplitBoth;
    else
      return Continue;
  }

  void
  addWord(const UnicodeString &word_text)
  {
    UnicodeString new_word_text = word_text;
    new_word_text.trim();
    mru::Tokenizer::addWord(new_word_text);
  }
};

void
Tokenizer_tests::space_strip(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  WORD("aa");
  WORD("b");
  WORD("cc");
  WORD("dd");

  SpaceStripingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class SpaceMergingTokenizer : public mru::Tokenizer {
public:
  SpaceMergingTokenizer(void)
    : in_whitespace(false)
  { }

  ActionKind
  actionOn(UChar current_character)
  {
    bool is_whitespace = u_isWhitespace(current_character);
    if (!in_whitespace && is_whitespace) {
      in_whitespace = true;
      return SplitLeft;
    } else if (in_whitespace && !is_whitespace) {
      in_whitespace = false;
      return SplitLeft;
    } else if (in_whitespace && is_whitespace) {
      return Continue;
    } else { //if (!in_whitespace && !is_whitespace)
      return Continue;
    }
  }
private:
  bool in_whitespace;
};

void
Tokenizer_tests::space_merge(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  WORD("aa");
  WORD(" ");
  WORD("b");
  WORD("  ");
  WORD("cc");
  WORD("  ");
  WORD("dd");

  SpaceMergingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class SpaceTrimingTokenizer : public SpaceMergingTokenizer {
public:
  void
  addWord(const UnicodeString &word_text)
  {
    if (isWhitespace(word_text))
      mru::Tokenizer::addWord(UChar(' '));
    else
      mru::Tokenizer::addWord(word_text);
  }

private:
  bool
  isWhitespace(const UnicodeString &text)
  {
    icu::StringCharacterIterator iter(text);
    for (UChar current_char = iter.first(); iter.hasNext(); current_char = iter.next()) {
      if (!u_isWhitespace(current_char))
        return false;
    }
    return true;
  }
};

void
Tokenizer_tests::space_trimming(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  WORD("aa");
  WORD(" ");
  WORD("b");
  WORD(" ");
  WORD("cc");
  WORD(" ");
  WORD("dd");

  SpaceTrimingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class EscapeSequenceTokenizer : public mru::Tokenizer {
public:
  EscapeSequenceTokenizer(void)
    : escape_next(false)
  { }

  ActionKind
  actionOn(UChar current_character)
  {
    if (escape_next) {
      escape_next = false;
      return Continue;
    } else if (current_character == UChar('\\')) {
      escape_next = true;
      return Ignore;
    } else if (current_character == UChar('|'))
      return SplitBoth;
    else
      return Continue;
  }
private:
  bool escape_next;
};

void
Tokenizer_tests::escape_sequence(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd\\|ef");

  WORD("ab");
  WORD("|");
  WORD("cd|ef");

  EscapeSequenceTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

class ConstantSizeTokenizer : public mru::Tokenizer {
public:
  ConstantSizeTokenizer(int size)
    : counter(0), split_size(size)
  { }

  ActionKind
  actionOn(UChar current_character)
  {
    if (++counter > split_size) {
      counter = 1;
      return SplitLeft;
    } else
      return Continue;
  }
private:
  int counter;
  int split_size;
};

void
Tokenizer_tests::constant_size(void)
{
  expr_str = glue_cast<UnicodeString>("abc123def456");

  WORD("abc");
  WORD("123");
  WORD("def");
  WORD("456");

  ConstantSizeTokenizer tokenizer(3);
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

void
Tokenizer_tests::static_join(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");
  BothSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, Tokenizer::joinWords(words));
}

void
Tokenizer_tests::join(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");
  BothSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  CPPUNIT_ASSERT_EQUAL(expr_str, tokenizer.joinWords(words));
}

void
Tokenizer_tests::get_words(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");
  BothSplitingTokenizer tokenizer;
  const Tokenizer::WordList &words = tokenizer.tokenize(expr_str);

  expected_words = words;

  compare_word_lists(words);
}

/* ------------------------------------------------------------------------- */

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(Tokenizer_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

