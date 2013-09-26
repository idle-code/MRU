#include "ExtMetatag.hpp"

namespace mru
{

void
ExtMetatag::initialize(MruCore *core, const UnicodeString &a_arguments)
{

}

UnicodeString
ExtMetatag::execute(const FilePath &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(a_file_path.extension());
}

} /* namespace mru */

