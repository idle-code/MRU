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
  if(a_file_path.directory().length() == 0)
    return UnicodeString();
  else
    return a_file_path.directory() + glue_cast<UnicodeString>("/");
}

} /* namespace mru */

