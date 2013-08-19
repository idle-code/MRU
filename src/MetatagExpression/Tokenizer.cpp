#include "MetatagExpression/Tokenizer.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

namespace mru {
namespace MetatagExpression {

Tokenizer::Tokenizer(const ConstUnicodeStringIterator &text_iterator)
  : TokenizerBase(text_iterator), escape_next(false)
{ first(); }

Tokenizer::ActionKind
Tokenizer::actionOn(UChar current_character)
{
  if (escape_next) {
    escape_next = false;
    return Continue;
  }

  if (isControlCharacter(current_character)) {
    if (current_character == UChar('\\'))
      escape_next = true;
    return SplitBoth;
  } else
    return Continue;
}

bool
Tokenizer::isControlCharacter(UChar character) const
{
  switch(character) {
    case UChar('%'):
    case UChar('('):
    case UChar(')'):
    case UChar('{'):
    case UChar('}'):
    case UChar('\\'):
      return true;
    default:
      return false;
  }
}

} /* namespace MetatagExpression */
} /* namespace mru */

