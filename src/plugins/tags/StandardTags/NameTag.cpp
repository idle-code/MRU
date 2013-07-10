#include "NameTag.hpp"

namespace mru
{

NameTag::NameTag(void)
  : TagPlugin(static_implementation_name())
{ }

NameTag::~NameTag(void)
{ }

void
NameTag::initialize(const UnicodeString &a_arguments)
{ }

UnicodeString
NameTag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(
      glue_cast<FilePath>(a_file_path.getFilePath()).stem()
      );
}

} /* namespace mru */

