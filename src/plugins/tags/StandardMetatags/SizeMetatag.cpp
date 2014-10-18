#include "SizeMetatag.hpp"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

namespace mru {

SizeMetatag::SizeMetatag(void)
{ }

void
SizeMetatag::initialize(MruCore *, const UnicodeString &)
{ }

UnicodeString
SizeMetatag::execute(const FilePath &file_path, const UnicodeString &)
{
  try {
    unsigned long file_size = boost::filesystem::file_size(file_path);
    return glue_cast<UnicodeString>(boost::lexical_cast<std::string>(file_size));
  } catch (std::exception &e) {
    ERR(e.what());
    throw MetatagBase::Exception(glue_cast<UnicodeString>("Cannot get file size for ") + glue_cast<UnicodeString>(file_path));
  }
}

} /* namespace mru */

