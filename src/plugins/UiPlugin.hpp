#ifndef UI_PLUGIN_HPP
#define UI_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"

namespace mru
{

class UiPlugin : public MruPlugin {
public:
  typedef PluginManager<UiPlugin> Manager;
  typedef void (*RegisterFunctionType)(Manager::Pointer);
  static const char* RegisterFunctionName(void) { return "register_ui_plugin"; }

  typedef boost::shared_ptr<UiPlugin> Pointer;
  
  virtual int start(int argc, char *argv[]) = 0;
};

} /* namespace mru */

#define EXPORT_UI_PLUGIN_FACTORY(factory) \
  extern "C" { \
    void register_ui_plugin(mru::UiPlugin::Manager::Pointer plugin_manager) { \
      assert(plugin_manager); \
      plugin_manager->registerFactory(factory); \
    } \
  }


#endif /* UI_PLUGIN_HPP */

