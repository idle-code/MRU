#ifndef UI_PLUGIN_HPP
#define UI_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"

namespace mru
{

class UiPlugin : public MruPlugin {
public:
  typedef PluginManager<UiPlugin> Manager;
  typedef DynamicPluginManager<UiPlugin> DynamicManager;
  typedef void (*RegisterFunctionType)(Manager::Pointer);
  static const char* getRegisterFunctionName(void) { return "registerUiPluginFactory"; }

  typedef boost::shared_ptr<UiPlugin> Pointer;
  
  virtual int start(int argc, char *argv[]) = 0;
};

} /* namespace mru */

#endif /* UI_PLUGIN_HPP */

