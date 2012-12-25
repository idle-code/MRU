#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <registry.hpp>
#include <patterns.hpp>
#include <unicode/unistr.h> //for ICU UnicodeString
//#include <boost/locale.hpp>

namespace mru
{

typedef std::string filepath_type;
typedef std::string filename_type;
typedef data_tree::registry registry;
typedef data_tree::registry::name_type name_type; 
typedef icu::UnicodeString string_type;
typedef icu::UnicodeString UnicodeString;

typedef singleton<registry> reg;

} /* namespace mru */

#endif /* TYPES_HPP */

