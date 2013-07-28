#include "Tokenizer.hpp"
#include <unicode/uchar.h>
#include <unicode/schriter.h>

namespace mru
{

UnicodeString
Tokenizer::joinWords(const WordList &word_list)
{
  UnicodeString joined_string;
  WordList::const_iterator ti_end = word_list.end();
  for(WordList::const_iterator ti = word_list.begin(); ti != ti_end; ++ti)
    joined_string += *ti;
  return joined_string;
}

Tokenizer::Tokenizer(void)
{ }

Tokenizer::~Tokenizer(void)
{ }

const Tokenizer::WordList &
Tokenizer::tokenize(const UnicodeString &text)
{
  words.clear();

  icu::StringCharacterIterator iter(text);
  for (UChar current_char = iter.first(); iter.hasNext(); current_char = iter.next()) {
    switch(actionOn(current_char)) {
      case Continue:
        word += current_char;
        break;
      case SplitLeft:
        addWord(word);
        word = current_char;
        break;
      case SplitRight:
        word += current_char;
        addWord(word);
        word = UnicodeString();
        break;
      case SplitBoth:
        addWord(word);
        addWord(current_char);
        word = UnicodeString();
        break;
      case Ignore:
        break;
    }
  }

  addWord(word);

  return words;
}

const Tokenizer::WordList &
Tokenizer::getWords(void) const
{
  return words;
}

UnicodeString
Tokenizer::joinWords(void) const
{
  return joinWords(words);
}

/* ------------------------------------------------------------------------- */

void
Tokenizer::addWord(const UnicodeString &word_text)
{
  if (!word_text.isEmpty())
    words.push_back(word_text);
}

const UnicodeString &
Tokenizer::currentWord(void) const
{
  return word;
}

} /* namespace mru */

