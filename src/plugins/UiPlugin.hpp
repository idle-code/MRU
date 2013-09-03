#ifndef UI_PLUGIN_HPP
#define UI_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "plugin_manager.hpp"

namespace mru
{

class UiPlugin : public MruPlugin {
public:
  typedef UiPlugin self_type;
  typedef boost::shared_ptr<UiPlugin> Pointer;
public:
  PLUGIN_INTERFACE("UiPlugin")
  UiPlugin(const name_type &name)
    : MruPlugin(static_interface_name(), name)
  { }
  virtual ~UiPlugin(void)
  { }
  
  virtual int start(int argc, char *argv[]) = 0;
};

typedef plugin_manager<UiPlugin> UiPluginManager;

} /* namespace mru */

#endif /* UI_PLUGIN_HPP */

