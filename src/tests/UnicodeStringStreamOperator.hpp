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

//#define VAL(X) \
//  std::cout << #X ": '" << (X) << "'" << std::endl;
//#define MSG(X) \
//  std::cout << X << std::endl;

#endif /* UNICODE_STRING_STREAM_OPERATOR_HPP */

