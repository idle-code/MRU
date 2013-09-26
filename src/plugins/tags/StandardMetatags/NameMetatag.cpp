#include "NameMetatag.hpp"

namespace mru
{

void
NameMetatag::initialize(MruCore *core, const UnicodeString &a_arguments)
{ }

UnicodeString
NameMetatag::execute(const FilePath &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(a_file_path.stem());
}

} /* namespace mru */

