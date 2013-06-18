#ifndef UI_PLUGIN_HPP
#define UI_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "plugin_manager.hpp"

namespace mru
{

class UiPlugin : public MruPlugin {
public:
  typedef UiPlugin self_type;
public:
  PLUGIN_INTERFACE("UiPlugin")
  UiPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }
  virtual ~UiPlugin(void)
  { }
  
  virtual int start(int a_argc, char *a_argv[]) = 0;
};

typedef plugin_manager<UiPlugin> UiPluginManager;

} /* namespace mru */

#endif /* UI_PLUGIN_HPP */

