#ifndef GLUE_IMPL_HPP
#  error "This is implementation file. Use glue.hpp instead."
#else

#include <unicode/utypes.h>
#include <unicode/numfmt.h>
#include <sstream>
#include <boost/locale.hpp>

namespace mru
{

/* ------------------------------------------------------------------------- */

template<> inline
std::string
glue_cast<std::string, std::wstring>(const std::wstring &value)
{
  return std::string(value.begin(), value.end());
}

template<> inline
std::wstring
glue_cast<std::wstring, std::string>(const std::string &value)
{
  return std::wstring(value.begin(), value.end());
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, std::wstring>(const std::wstring &value)
{
  if(sizeof(UChar) == sizeof(std::wstring::value_type))
    return UnicodeString(reinterpret_cast<const UChar*>(value.c_str()));
  else //if(sizeof(UChar) == 2 && sizeof(std::wstring::value_type) == 4)
    return UnicodeString::fromUTF32(reinterpret_cast<const UChar32*>(value.c_str()), value.length());
}

template<> inline
std::wstring
glue_cast<std::wstring, UnicodeString>(const UnicodeString &value)
{
  const UChar *value_buffer = value.getBuffer();
  return std::wstring(value_buffer, value_buffer + value.length());
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, std::string>(const std::string &value)
{
  return UnicodeString::fromUTF8(StringPiece(value.c_str()));
  //return UnicodeString(value.c_str(), value.length());
}

template<> inline
std::string
glue_cast<std::string, UnicodeString>(const UnicodeString &value)
{
  std::string result;
  value.toUTF8String(result);
  return result;
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, FilePath>(const FilePath &value)
{
  return glue_cast<UnicodeString>(value.generic_wstring());
}

template<> inline
FilePath
glue_cast<FilePath, UnicodeString>(const UnicodeString &value)
{
  return FilePath(glue_cast<std::wstring>(value));
}

/* ------------------------------------------------------------------------- */

template<> inline
std::string
glue_cast<std::string, FilePath>(const FilePath &value)
{
  return value.generic_string();
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, int>(const int &value)
{
  std::wstringstream ss;
  ss << boost::locale::as::number << value;  
  return glue_cast<UnicodeString>(ss.str());
}

/* ------------------------------------------------------------------------- */

inline std::ostream &
operator<<(std::ostream &out, const UnicodeString &ustr)
{
  return out << glue_cast<std::string>(ustr);
}

} /* namespace mru */

#endif

