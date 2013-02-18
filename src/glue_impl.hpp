#ifndef GLUE_IMPL_HPP
#  error "This is implementation file. Use glue.hpp instead."
#else

namespace mru
{

template<> inline
std::string
glue_cast<std::string, UnicodeString>(const UnicodeString &a_value)
{
  std::string result;
  return a_value.toUTF8String(result);
}

template<> inline
UnicodeString
glue_cast<UnicodeString, std::string>(const std::string &a_value)
{
  return UnicodeString(a_value.c_str(), a_value.length());
}

/* ------------------------------------------------------------------------- */

template<> inline
wxString
glue_cast<wxString, UnicodeString>(const UnicodeString &a_value)
{
  std::string result;
  return wxString(a_value.toUTF8String(result).c_str(), wxConvUTF8);
}

template<> inline
UnicodeString
glue_cast<UnicodeString, wxString>(const wxString &a_value)
{
  wxCharBuffer buff = a_value.utf8_str(); 
  return UnicodeString(buff, a_value.Length());
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
  std::string path_repr = a_value.generic_string();
  wxCharBuffer buff = path_repr.c_str(); 
  return UnicodeString(buff, path_repr.length());
}

template<> inline
filepath_type
glue_cast<filepath_type, UnicodeString>(const UnicodeString &a_value)
{
  return filepath_type(glue_cast<std::string>(a_value));
}

} /* namespace mru */

#endif

