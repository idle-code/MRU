#include "MruPlugin.hpp"
#include "MruCore.hpp"

namespace mru
{

MruPlugin::MruPlugin(void)
  : core(NULL)
{ }

MruPlugin::~MruPlugin(void)
{ }

bool
MruPlugin::Init(MruCore *mru_core)
{
  if(mru_core == NULL)
    return false;

  core = mru_core;
  return true;
}

MruCore *
MruPlugin::getCore(void)
{
  return core;
}

} /* namespace mru */

