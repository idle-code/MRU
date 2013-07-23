#include "MruPlugin.hpp"
#include "MruCore.hpp"

namespace mru
{

MruPluginException::MruPluginException(const std::string &module, const UnicodeString &message)
  : module(module), message(message)
{ }

MruPluginException::MruPluginException(const std::string &module, const std::string &message)
  : module(module), message(glue_cast<UnicodeString>(message))
{ }

MruPluginException::~MruPluginException(void) throw()
{ }

const char *
MruPluginException::what(void) const throw()
{
  return glue_cast<std::string>(message).c_str();
}

const UnicodeString &
MruPluginException::getMessage(void) const throw()
{
  return message;
}

/* ------------------------------------------------------------------------- */

MruPlugin::MruPlugin(const name_type &interface, const name_type &name)
  : plugin<MruPlugin>(interface, name), core(NULL)
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

