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
DirTag::execute(const UnicodeString &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>("Invalid");
}

} /* namespace mru */

