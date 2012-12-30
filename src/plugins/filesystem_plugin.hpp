#ifndef FILESYSTEM_PLUGIN_HPP
#define FILESYSTEM_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "plugin_manager.hpp"

namespace mru
{

class FilesystemPlugin : public MruPlugin {
public:
  typedef FilesystemPlugin self_type;
public:
  PLUGIN_INTERFACE("FilesystemPlugin")
  FilesystemPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }
  virtual ~FilesystemPlugin(void)
  { }
};

typedef plugin_manager<FilesystemPlugin> FilesystemPluginManager;

} /* namespace mru */

#endif /* FILESYSTEM_PLUGIN_HPP */

