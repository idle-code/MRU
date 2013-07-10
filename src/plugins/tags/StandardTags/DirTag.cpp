#include "DirTag.hpp"

namespace mru
{

DirTag::DirTag(void)
  : TagPlugin(static_implementation_name())
{ }

DirTag::~DirTag(void)
{ }

void
DirTag::initialize(const UnicodeString &a_arguments)
{

}

UnicodeString
DirTag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)
{
  if(bfs::is_empty(a_file_path.getFilePath().parent_path()) == 0)
    return UnicodeString();
  else
    return glue_cast<UnicodeString>(a_file_path.getFilePath().parent_path()) + glue_cast<UnicodeString>("/");
}

} /* namespace mru */

