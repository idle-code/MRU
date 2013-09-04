#include "ExtMetatag.hpp"

namespace mru
{

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

