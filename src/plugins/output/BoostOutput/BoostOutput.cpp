#include "BoostOutput.hpp"

namespace mru
{


BoostOutput::BoostOutput(void)
  : OutputPlugin(static_implementation_name())
{ }

BoostOutput::~BoostOutput(void)
{ }

bool
BoostOutput::rename(const FilePath &a_name, const FilePath &a_new_name)
{
  FO("BoostOutput::rename(const FilePath &a_name, const FilePath &a_new_name)");

  return false;
}

} /* namespace mru */

