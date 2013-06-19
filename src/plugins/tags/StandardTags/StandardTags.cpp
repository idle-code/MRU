#include "StandardTags.hpp"

namespace mru
{

Count::Count(void)
  : TagPlugin(static_implementation_name())
{ }

Count::~Count(void)
{ }

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::Count)
EXPORT_END

