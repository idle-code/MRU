#include "NameMetatag.hpp"

namespace mru
{

NameMetatag::NameMetatag(void)
  : MetatagPlugin(static_implementation_name())
{ }

NameMetatag::~NameMetatag(void)
{ }

void
NameMetatag::initialize(const UnicodeString &a_arguments)
{ }

UnicodeString
NameMetatag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(
      glue_cast<FilePath>(a_file_path.getCurrent()).stem()
      );
}

} /* namespace mru */

