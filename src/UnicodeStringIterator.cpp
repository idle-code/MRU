#include "UnicodeStringIterator.hpp"

namespace mru {

ConstUnicodeStringIterator::ConstUnicodeStringIterator(const UnicodeString &text)
  : iter(text)
{
  first();
}

void
ConstUnicodeStringIterator::first(void)
{
  iter.first();
}

bool
ConstUnicodeStringIterator::next(void)
{
  if (atEnd())
    return false;
  assert(!atEnd());
  iter.next();
  return !atEnd();
}

bool
ConstUnicodeStringIterator::atEnd(void) const
{
  return !iter.hasNext();
}

UChar
ConstUnicodeStringIterator::getCurrent(void) const
{
  return iter.current();
}

} /* namespace mru */

