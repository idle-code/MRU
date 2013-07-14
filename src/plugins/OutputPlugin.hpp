#ifndef OUTPUT_PLUGIN_HPP
#define OUTPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"

namespace mru
{

class OutputPluginException : public MruPluginException {
public:
  OutputPluginException(const UnicodeString &a_message)
    : MruPluginException("OutputPlugin", a_message)
  { }
  OutputPluginException(const std::string &a_message)
    : MruPluginException("OutputPlugin", a_message)
  { }
};

/* ------------------------------------------------------------------------- */

class OutputPlugin : public MruPlugin {
public:
  typedef OutputPlugin self_type;
public:
  PLUGIN_INTERFACE("OutputPlugin")
  OutputPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }
  virtual ~OutputPlugin(void)
  { }

  virtual bool rename(const FilePath &a_name, const FilePath &a_new_name) = 0;
};

typedef plugin_manager<OutputPlugin> OutputPluginManager;

} /* namespace mru */

#endif /* OUTPUT_PLUGIN_HPP */

