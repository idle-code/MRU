#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "patterns.hpp"
#include <unicode/unistr.h> //for ICU UnicodeString
#include <wx/string.h>
#include <boost/filesystem.hpp>
#include <debug_l.h>

namespace mru
{

typedef boost::property_tree::ptree registry;
typedef boost::property_tree::ptree::key_type name_type;
typedef boost::filesystem::wpath FilePath;
namespace bfs = boost::filesystem;

typedef singleton<registry> reg;

} /* namespace mru */

#endif /* TYPES_HPP */

