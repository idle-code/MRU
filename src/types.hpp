#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <data_tree/registry.hpp>
#include "patterns.hpp"
#include <unicode/unistr.h> //for ICU UnicodeString
#include <wx/string.h>
#include <boost/filesystem.hpp>
//#include <boost/locale.hpp>

namespace mru
{

//typedef std::string filename_type;
//typedef std::string filepath_type;
typedef data_tree::registry registry;
typedef data_tree::registry::name_type name_type; 
typedef icu::UnicodeString string_type;
typedef icu::UnicodeString UnicodeString;
//typedef icu::UnicodeString filepath_type;
typedef boost::filesystem::path filepath_type;

std::string UnicodeString2STLString(const UnicodeString &a_string);
UnicodeString STLString2UnicodeString(const std::string &a_string);

wxString UnicodeString2wxString(const UnicodeString &a_string);
UnicodeString wxString2UnicodeString(const wxString &a_string);

wxString Filepath2wxString(const filepath_type &a_path);
filepath_type wxString2Filepath(const wxString &a_path);

typedef singleton<registry> reg;

} /* namespace mru */

#endif /* TYPES_HPP */

