#include "TokenizerBase.hpp"
#include <unicode/uchar.h>
#include <unicode/schriter.h>

namespace mru {

TokenizerBase::TokenizerBase(const ConstUnicodeStringIterator &text_iterator)
  : text_iterator(text_iterator), next_character_is_word(false)
{ }

void
TokenizerBase::first(void)
{
  text_iterator.first();
  next_character = 0;
  next_character_is_word = false;
  current_word = tokenizeNext();
}

bool
TokenizerBase::next(void)
{
  assert(!atEnd());
  current_word = tokenizeNext();
  return !atEnd();
}

bool
TokenizerBase::atEnd(void) const
{
  return current_word.isEmpty();
}

UnicodeString
TokenizerBase::getCurrent(void) const
{
  assert(!atEnd());
  return current_word;
}

/* ------------------------------------------------------------------------- */

UnicodeString
TokenizerBase::tokenizeNext(void)
{
  word.remove();

  UChar current_char;
  do {
    if (next_character != 0) {
      word += next_character;
      next_character = 0;
      if (next_character_is_word && finishUpWord())
        break;
    }

    current_char = readNext();
    if (current_char == 0)
      break; 

    if (splitOn(current_char) && finishUpWord())
      break;

  } while(true);

  return word;
}

bool
TokenizerBase::finishUpWord(void)
{
  if (word.isEmpty())
    return false;
  word = yieldWord(word);
  return !word.isEmpty();
}

UChar
TokenizerBase::readNext(void)
{
  if (text_iterator.atEnd())
    return 0;
  UChar character = text_iterator.getCurrent();
  text_iterator.next();
  return character;
}

bool
TokenizerBase::splitOn(UChar current_char)
{
  switch(actionOn(current_char)) {
    case Continue:
      word += current_char;
      break;

    case SplitLeft:
      next_character = current_char;
      return true;

    case SplitRight:
      word += current_char;
      return true;

    case SplitBoth:
      next_character = current_char;
      next_character_is_word = true;
      return true;

    case Ignore:
      break;
  }

  return false;
}

UnicodeString
TokenizerBase::yieldWord(const UnicodeString &word)
{
  return word;
}

/* ------------------------------------------------------------------------- */

} /* namespace mru */

