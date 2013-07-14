#include "MruPlugin.hpp"
#include "MruCore.hpp"

namespace mru
{

MruPluginException::MruPluginException(const std::string &a_module, const UnicodeString &a_message)
  : m_module(a_module), m_message(a_message)
{ }

MruPluginException::MruPluginException(const std::string &a_module, const std::string &a_message)
  : m_module(a_module), m_message(glue_cast<UnicodeString>(a_message))
{ }

MruPluginException::~MruPluginException(void) throw()
{ }

const char *
MruPluginException::what(void) const throw()
{
  return glue_cast<std::string>(m_message).c_str();
}

const UnicodeString &
MruPluginException::message(void) const throw()
{
  return m_message;
}

/* ------------------------------------------------------------------------- */

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

