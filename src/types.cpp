#include "types.hpp"

namespace mru
{

std::string
UnicodeString2STLString(const UnicodeString &a_string)
{
  std::string result;
  return a_string.toUTF8String(result);
}

UnicodeString
STLString2UnicodeString(const std::string &a_string)
{
  return UnicodeString(a_string.c_str(), a_string.length());

}

} /* namespace mru */

