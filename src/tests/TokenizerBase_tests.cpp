#include "TokenizerBase_tests.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

void
TokenizerBase_tests::setUp(void)
{
  expr_str = UnicodeString();
  expected_words.clear();
}

void
TokenizerBase_tests::compare_to_expected(TokenizerBase &tokenizer)
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

class NotSplitingTokenizer : public mru::TokenizerBase {
public:
  NotSplitingTokenizer(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    return Continue;
  }
};

void
TokenizerBase_tests::no_split(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd");

  WORD("ab|cd");

  NotSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class LeftSplitingTokenizer : public mru::TokenizerBase {
public:
  LeftSplitingTokenizer(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitLeft;
    return Continue;
  }
};

void
TokenizerBase_tests::simple_split_left(void)
{
  expr_str = glue_cast<UnicodeString>("|ab|cd|");

  WORD("|ab");
  WORD("|cd");
  WORD("|");

  LeftSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

void
TokenizerBase_tests::split_left(void)
{
  expr_str = glue_cast<UnicodeString>("|||");

  WORD("|");
  WORD("|");
  WORD("|");

  LeftSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class RightSplitingTokenizer : public mru::TokenizerBase {
public:
  RightSplitingTokenizer(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitRight;
    return Continue;
  }
};

void
TokenizerBase_tests::simple_split_right(void)
{
  expr_str = glue_cast<UnicodeString>("|ab|cd|");

  WORD("|");
  WORD("ab|");
  WORD("cd|");

  RightSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

void
TokenizerBase_tests::split_right(void)
{
  expr_str = glue_cast<UnicodeString>("|||");

  WORD("|");
  WORD("|");
  WORD("|");

  RightSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class BothSplitingTokenizer : public mru::TokenizerBase {
public:
  BothSplitingTokenizer(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitBoth;
    return Continue;
  }
};

void
TokenizerBase_tests::simple_split_both(void)
{
  expr_str = glue_cast<UnicodeString>("|ab|cd|");

  WORD("|");
  WORD("ab");
  WORD("|");
  WORD("cd");
  WORD("|");

  BothSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

void
TokenizerBase_tests::split_both(void)
{
  expr_str = glue_cast<UnicodeString>("|||");

  WORD("|");
  WORD("|");
  WORD("|");

  BothSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class MixedSplitingTokenizer : public mru::TokenizerBase {
public:
  MixedSplitingTokenizer(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    if (current_character == UChar('|'))
      return SplitBoth;
    else if (current_character == UChar('<'))
      return SplitLeft;
    else if (current_character == UChar('>'))
      return SplitRight;
    return Continue;
  }
};

void
TokenizerBase_tests::mixed_split(void)
{
  expr_str = glue_cast<UnicodeString>("<>|><||>|<");

  WORD("<>");
  WORD("|");
  WORD(">");
  WORD("<");
  WORD("|");
  WORD("|");
  WORD(">");
  WORD("|");
  WORD("<");

  MixedSplitingTokenizer tokenizer(expr_str);
  compare_to_expected(tokenizer);

}

/* ------------------------------------------------------------------------- */

class SpaceStripingTokenizerBase : public mru::TokenizerBase {
public:
  SpaceStripingTokenizerBase(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    if (u_isWhitespace(current_character))
      return SplitBoth;
    else
      return Continue;
  }

  UnicodeString
  yieldWord(const UnicodeString &word)
  {
    UnicodeString new_word = word;
    new_word.trim();
    return new_word;
  }
};

void
TokenizerBase_tests::space_strip(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  WORD("aa");
  WORD("b");
  WORD("cc");
  WORD("dd");

  SpaceStripingTokenizerBase tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class SpaceMergingTokenizerBase : public mru::TokenizerBase {
public:
  SpaceMergingTokenizerBase(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator), in_whitespace(false)
  { first(); }

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
TokenizerBase_tests::space_merge(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  WORD("aa");
  WORD(" ");
  WORD("b");
  WORD("  ");
  WORD("cc");
  WORD("  ");
  WORD("dd");

  SpaceMergingTokenizerBase tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class SpaceTrimingTokenizerBase : public SpaceMergingTokenizerBase {
public:
  SpaceTrimingTokenizerBase(const ConstUnicodeStringIterator &text_iterator)
    : SpaceMergingTokenizerBase(text_iterator)
  { first(); }

  UnicodeString
  yieldWord(const UnicodeString &word)
  {
    if (isWhitespace(word))
      return UChar(' ');
    else
      return word;
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
TokenizerBase_tests::space_trimming(void)
{
  expr_str = glue_cast<UnicodeString>("aa b  cc  dd");

  WORD("aa");
  WORD(" ");
  WORD("b");
  WORD(" ");
  WORD("cc");
  WORD(" ");
  WORD("dd");

  SpaceTrimingTokenizerBase tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class EscapeSequenceTokenizerBase : public mru::TokenizerBase {
public:
  EscapeSequenceTokenizerBase(const ConstUnicodeStringIterator &text_iterator)
    : TokenizerBase(text_iterator), escape_next(false)
  { first(); }

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
TokenizerBase_tests::escape_sequence(void)
{
  expr_str = glue_cast<UnicodeString>("ab|cd\\|ef");

  WORD("ab");
  WORD("|");
  WORD("cd|ef");

  EscapeSequenceTokenizerBase tokenizer(expr_str);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

class ConstantSizeTokenizerBase : public mru::TokenizerBase {
public:
  ConstantSizeTokenizerBase(const ConstUnicodeStringIterator &text_iterator, int size)
    : TokenizerBase(text_iterator), counter(0), split_size(size)
  { first(); }

  ActionKind
  actionOn(UChar current_character)
  {
    if (++counter == split_size) {
      counter = 0;
      return SplitRight;
    } else
      return Continue;
  }
private:
  int counter;
  int split_size;
};

void
TokenizerBase_tests::constant_size(void)
{
  expr_str = glue_cast<UnicodeString>("abc123def456");

  WORD("abc");
  WORD("123");
  WORD("def");
  WORD("456");

  ConstantSizeTokenizerBase tokenizer(expr_str, 3);
  compare_to_expected(tokenizer);
}

/* ------------------------------------------------------------------------- */

TokenizerBase_tests::ValueList
TokenizerBase_tests::getSampleValues(void)
{
  ValueList values;
  values.push_back(glue_cast<UnicodeString>("abc"));
  values.push_back(glue_cast<UnicodeString>("123"));
  values.push_back(glue_cast<UnicodeString>("def"));
  values.push_back(glue_cast<UnicodeString>("456"));
  return values;
}

mru::ConstIterator<UnicodeString>::Pointer
TokenizerBase_tests::getConstIterator(const ValueList &values_in_container)
{
  for(ValueList::const_iterator i = values_in_container.begin(); i != values_in_container.end(); ++i) {
    expr_str += *i;
  }

  return TokenizerBase::Pointer(new ConstantSizeTokenizerBase(expr_str, 3));
}

/* ------------------------------------------------------------------------- */

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(TokenizerBase_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

