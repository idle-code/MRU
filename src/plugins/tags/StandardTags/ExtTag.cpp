#include "ExtTag.hpp"

namespace mru
{

ExtTag::ExtTag(void)
  : TagPlugin(static_implementation_name())
{ }

ExtTag::~ExtTag(void)
{ }

void
ExtTag::initialize(const UnicodeString &a_arguments)
{

}

UnicodeString
ExtTag::execute(const UnicodeString &a_file_path, const UnicodeString &a_area_of_effect)
{
  return glue_cast<UnicodeString>(
      glue_cast<filepath_type>(a_file_path).extension()
      );
}

} /* namespace mru */

