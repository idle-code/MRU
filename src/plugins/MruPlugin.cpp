#include "MruPlugin.hpp"
#include "MruCore.hpp"

namespace mru
{

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

/* ------------------------------------------------------------------------- */

MruPlugin::Exception::Exception(const std::string &module, const UnicodeString &message)
  : module(module), message(message)
{ }

MruPlugin::Exception::Exception(const std::string &module, const std::string &message)
  : module(module), message(glue_cast<UnicodeString>(message))
{ }

MruPlugin::Exception::~Exception(void) throw()
{ }

const char *
MruPlugin::Exception::what(void) const throw()
{
  return glue_cast<std::string>(message).c_str();
}

const UnicodeString &
MruPlugin::Exception::getMessage(void) const throw()
{
  return message;
}

} /* namespace mru */

