#include "MruPlugin.hpp"
#include "MruCore.hpp"

namespace mru
{

MruPlugin::MruPlugin(const name_type &a_interface, const name_type &a_name)
  : plugin<MruPlugin>(a_interface, a_name), m_core(NULL)
{ }

MruPlugin::~MruPlugin(void)
{ }

bool
MruPlugin::Init(MruCore *a_mru_core)
{
  if(a_mru_core == NULL)
    return false;

  m_core = a_mru_core;
  return true;
}

MruCore*
MruPlugin::core(void)
{
  return m_core;
}

} /* namespace mru */

