#ifndef GLUE_EXTENSION_HPP
#define GLUE_EXTENSION_HPP

#include "glue.hpp"

namespace mru
{

/* ------------------------------------------------------------------------- */

template<> inline
FilePath
glue_cast<FilePath, wxString>(const wxString &value)
{
  return FilePath(value.mb_str());
}

template<> inline
wxString
glue_cast<wxString, FilePath>(const FilePath &value)
{
  return wxString(value.c_str(), wxConvUTF8);
}

template<> inline
wxString
glue_cast<wxString, std::string>(const std::string &value)
{
  return wxString(value.c_str(), wxConvUTF8);
}

template<> inline
std::string
glue_cast<std::string, wxString>(const wxString &value)
{
  return std::string(value.mb_str());
}

/* ------------------------------------------------------------------------- */

template<> inline
wxString
glue_cast<wxString, std::wstring>(const std::wstring &value)
{
  return wxString(value.c_str(), wxConvUTF8);
}

template<> inline
std::wstring
glue_cast<std::wstring, wxString>(const wxString &value)
{
  return std::wstring(value.wc_str());
}

/* ------------------------------------------------------------------------- */

template<> inline
UnicodeString
glue_cast<UnicodeString, wxString>(const wxString &value)
{
  return glue_cast<UnicodeString>(glue_cast<std::wstring>(value));
}

template<> inline
wxString
glue_cast<wxString, UnicodeString>(const UnicodeString &value)
{
  return glue_cast<wxString>(glue_cast<std::wstring>(value));
}

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* GLUE_EXTENSION_HPP */

