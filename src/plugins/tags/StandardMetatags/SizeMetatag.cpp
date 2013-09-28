#include "SizeMetatag.hpp"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

namespace mru
{

SizeMetatag::SizeMetatag(void)
{ }

void
SizeMetatag::initialize(MruCore *, const UnicodeString &)
{ }

UnicodeString
SizeMetatag::execute(const FilePath &file_path, const UnicodeString &)
{
  unsigned long file_size = boost::filesystem::file_size(file_path);
  return glue_cast<UnicodeString>(boost::lexical_cast<std::string>(file_size));
}

} /* namespace mru */

