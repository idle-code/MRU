#include "UnicodeStringStreamOperator.hpp"
#include "Tokenizer_tests.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>
#include "glue.hpp"

void
Tokenizer_tests::setUp(void)
{
  expr_str = UnicodeString();
  expected_tokens.clear();
}

void
Tokenizer_tests::compare_token_lists(const TokenList &provided_tokens)
{
  TokenList::const_iterator eti = expected_tokens.begin();
  TokenList::const_iterator ti = provided_tokens.begin();

  for(; eti != expected_tokens.end() && ti != provided_tokens.end(); ++eti, ++ti) {
    //std::cout << "'" << *eti << "' == '" << *ti << "'" << std::endl;
    CPPUNIT_ASSERT_EQUAL(*eti, *ti);
  }

  CPPUNIT_ASSERT(eti == expected_tokens.end());
  CPPUNIT_ASSERT(ti == provided_tokens.end());
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

  TOKEN("ab|cd");

  NotSplitingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

  TOKEN("ab");
  TOKEN("|cd");

  LeftSplitingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

  TOKEN("ab|");
  TOKEN("cd");

  RightSplitingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

  TOKEN("ab");
  TOKEN("|");
  TOKEN("cd");

  BothSplitingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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
  addToken(const UnicodeString &token_text)
  {
    UnicodeString new_token_text = token_text;
    new_token_text.trim();
    mru::Tokenizer::addToken(new_token_text);
  }
};

void
Tokenizer_tests::space_strip(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  TOKEN("aa");
  TOKEN("b");
  TOKEN("cc");
  TOKEN("dd");

  SpaceStripingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

  TOKEN("aa");
  TOKEN(" ");
  TOKEN("b");
  TOKEN("  ");
  TOKEN("cc");
  TOKEN("  ");
  TOKEN("dd");

  SpaceMergingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
}

/* ------------------------------------------------------------------------- */

class SpaceTrimingTokenizer : public SpaceMergingTokenizer {
public:
  void
  addToken(const UnicodeString &token_text)
  {
    if (isWhitespace(token_text))
      mru::Tokenizer::addToken(UChar(' '));
    else
      mru::Tokenizer::addToken(token_text);
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

  TOKEN("aa");
  TOKEN(" ");
  TOKEN("b");
  TOKEN(" ");
  TOKEN("cc");
  TOKEN(" ");
  TOKEN("dd");

  SpaceTrimingTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

  TOKEN("ab");
  TOKEN("|");
  TOKEN("cd|ef");

  EscapeSequenceTokenizer tokenizer;
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

  TOKEN("abc");
  TOKEN("123");
  TOKEN("def");
  TOKEN("456");

  ConstantSizeTokenizer tokenizer(3);
  const Tokenizer::TokenList &tokens = tokenizer.tokenize(expr_str);

  compare_token_lists(tokens);
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

