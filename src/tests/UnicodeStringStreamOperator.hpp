#ifndef UNICODE_STRING_STREAM_OPERATOR_HPP
#define UNICODE_STRING_STREAM_OPERATOR_HPP

#include "types.hpp"
#include "glue.hpp"
#include <ostream>

inline std::ostream &
operator<<(std::ostream &out, const UnicodeString &unicode_string)
{
  return out << mru::glue_cast<std::string>(unicode_string);
}

#endif /* UNICODE_STRING_STREAM_OPERATOR_HPP */

