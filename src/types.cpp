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

wxString
UnicodeString2wxString(const UnicodeString &a_string)
{
  std::string result;
  return wxString(a_string.toUTF8String(result).c_str(), wxConvUTF8);
}

UnicodeString
wxString2UnicodeString(const wxString &a_string)
{
  wxCharBuffer buff = a_string.utf8_str(); 
  return UnicodeString(buff, a_string.Length());
}

wxString
Filepath2wxString(const filepath_type &a_path)
{
  return wxString(a_path.c_str(), wxConvUTF8);
}

filepath_type
wxString2Filepath(const wxString &a_path)
{
  return filepath_type(a_path.mb_str());
}

} /* namespace mru */

