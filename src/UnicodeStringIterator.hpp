#ifndef UNICODE_STRING_ITERATOR_HPP
#define UNICODE_STRING_ITERATOR_HPP

#include "Iterator.hpp"
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/schriter.h>

namespace mru
{

class ConstUnicodeStringIterator : public ConstIterator<UChar> {
public:
  ConstUnicodeStringIterator(const UnicodeString &text);

  void first(void);
  bool next(void);
  bool atEnd(void) const;

  UChar getCurrent(void) const;

protected:
  mutable icu::StringCharacterIterator iter; //mutable used because .hasNext method is not const
};

} /* namespace mru */

#endif /* UNICODE_STRING_ITERATOR_HPP */

