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
UnicodeString
glue_cast<UnicodeString, filepath_type>(const filepath_type &a_value)
{
  return a_value.generic_wstring();
}

template<> inline
filepath_type
glue_cast<filepath_type, UnicodeString>(const UnicodeString &a_value)
{
  return filepath_type(a_value);
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, int>(const int &a_value)
{
  std::wstringstream ss;
  ss << boost::locale::as::number << a_value;  
  return ss.str();
}

} /* namespace mru */

#endif

