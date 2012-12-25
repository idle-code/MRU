#include "GenericBoostFSDriver.hpp"

namespace mru
{

GenericBoostFSDriver::GenericBoostFSDriver(void)
  : FilesystemPlugin(static_implementation_name())
{ }

GenericBoostFSDriver::~GenericBoostFSDriver(void)
{ }

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::GenericBoostFSDriver)
EXPORT_END


