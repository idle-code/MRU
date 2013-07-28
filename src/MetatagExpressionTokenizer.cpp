#include "MetatagExpressionTokenizer.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

namespace mru
{

MetatagExpressionTokenizer::MetatagExpressionTokenizer(void)
  : escape_next(false)
{ }

MetatagExpressionTokenizer::ActionKind
MetatagExpressionTokenizer::actionOn(UChar current_character)
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
MetatagExpressionTokenizer::isControlCharacter(UChar character) const
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

} /* namespace mru */

