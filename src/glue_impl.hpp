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
glue_cast<std::string, std::wstring>(const std::wstring &a_value)
{
  return std::string(a_value.begin(), a_value.end());
}

template<> inline
std::wstring
glue_cast<std::wstring, std::string>(const std::string &a_value)
{
  return std::wstring(a_value.begin(), a_value.end());
}

/* ------------------------------------------------------------------------- */

template<> inline
filepath_type
glue_cast<filepath_type, wxString>(const wxString &a_value)
{
  return filepath_type(a_value.mb_str());
}

template<> inline
wxString
glue_cast<wxString, filepath_type>(const filepath_type &a_value)
{
  return wxString(a_value.c_str(), wxConvUTF8);
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, std::wstring>(const std::wstring &a_value)
{
  if(sizeof(UChar) == sizeof(std::wstring::value_type))
    return UnicodeString(reinterpret_cast<const UChar*>(a_value.c_str()));
  else //if(sizeof(UChar) == 2 && sizeof(std::wstring::value_type) == 4)
    return UnicodeString::fromUTF32(reinterpret_cast<const UChar32*>(a_value.c_str()), a_value.length());
}

template<> inline
std::wstring
glue_cast<std::wstring, UnicodeString>(const UnicodeString &a_value)
{
  const UChar *value_buffer = a_value.getBuffer();
  return std::wstring(value_buffer, value_buffer + a_value.length());
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, std::string>(const std::string &a_value)
{
  return UnicodeString::fromUTF8(StringPiece(a_value.c_str()));
  //return UnicodeString(a_value.c_str(), a_value.length());
}

template<> inline
std::string
glue_cast<std::string, UnicodeString>(const UnicodeString &a_value)
{
  std::string result;
  a_value.toUTF8String(result);
  return result;
}

/* ------------------------------------------------------------------------- */

template<> inline
wxString
glue_cast<wxString, std::string>(const std::string &a_value)
{
  return wxString(a_value.c_str(), wxConvUTF8);
}

template<> inline
std::string
glue_cast<std::string, wxString>(const wxString &a_value)
{
  return std::string(a_value.mb_str());
}

/* ------------------------------------------------------------------------- */

template<> inline
wxString
glue_cast<wxString, std::wstring>(const std::wstring &a_value)
{
  return wxString(a_value.c_str(), wxConvUTF8);
}

template<> inline
std::wstring
glue_cast<std::wstring, wxString>(const wxString &a_value)
{
  return std::wstring(a_value.wc_str());
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, filepath_type>(const filepath_type &a_value)
{
  return glue_cast<UnicodeString>(a_value.generic_wstring());
}

template<> inline
filepath_type
glue_cast<filepath_type, UnicodeString>(const UnicodeString &a_value)
{
  return filepath_type(glue_cast<std::wstring>(a_value));
}

/* ------------------------------------------------------------------------- */

template<> inline
std::string
glue_cast<std::string, filepath_type>(const filepath_type &a_value)
{
  return a_value.generic_string();
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, int>(const int &a_value)
{
  std::wstringstream ss;
  ss << boost::locale::as::number << a_value;  
  return glue_cast<UnicodeString>(ss.str());
}

/* ------------------------------------------------------------------------- */

//template<> inline
//UnicodeString
//glue_cast<UnicodeString, wxString>(const wxString &a_value)
//{
//  return UnicodeString();
//}

template<> inline
wxString
glue_cast<wxString, UnicodeString>(const UnicodeString &a_value)
{
  return glue_cast<wxString>(glue_cast<std::wstring>(a_value));
}

/* ------------------------------------------------------------------------- */


} /* namespace mru */

#endif

