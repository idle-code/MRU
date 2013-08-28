#include "ExtMetatag.hpp"

namespace mru
{

ExtMetatag::ExtMetatag(void)
  : MetatagPlugin(static_implementation_name())
{ }

ExtMetatag::~ExtMetatag(void)
{ }

void
ExtMetatag::initialize(const UnicodeString &a_arguments)
{

}

UnicodeString
ExtMetatag::execute(const FileIterator::Pointer a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(
      glue_cast<FilePath>(a_file_path->getCurrent()).extension()
      );
}

} /* namespace mru */

