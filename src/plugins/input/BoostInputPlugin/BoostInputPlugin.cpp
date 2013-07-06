#include "BoostInputPlugin.hpp"

namespace mru
{

BoostInputPlugin::BoostInputPlugin(void)
  : InputPlugin(static_implementation_name())
{
  FO("BoostInputPlugin::BoostInputPlugin(void)");

}

BoostInputPlugin::~BoostInputPlugin(void)
{
  FO("BoostInputPlugin::~BoostInputPlugin(void)");
}


FileIterator *
BoostInputPlugin::getFileIterator(const FilePath &a_path)
{
  FO("BoostInputPlugin::getFileIterator(const FilePath &a_path)");
  return NULL;
}

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::BoostInputPlugin)
EXPORT_END

