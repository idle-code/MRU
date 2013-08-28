#include "DirMetatag.hpp"

namespace mru
{

DirMetatag::DirMetatag(void)
  : MetatagPlugin(static_implementation_name())
{ }

DirMetatag::~DirMetatag(void)
{ }

void
DirMetatag::initialize(const UnicodeString &a_arguments)
{

}

UnicodeString
DirMetatag::execute(const FileIterator::Pointer a_file_path, const UnicodeString &a_area_of_effect)
{
  if(bfs::is_empty(a_file_path->getCurrent().parent_path()) == 0)
    return UnicodeString();
  else
    return glue_cast<UnicodeString>(a_file_path->getCurrent().parent_path()) + glue_cast<UnicodeString>("/");
}

} /* namespace mru */

