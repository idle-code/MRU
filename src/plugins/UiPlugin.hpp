#ifndef UI_PLUGIN_HPP
#define UI_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"

namespace mru
{

class UiPlugin : public MruPlugin {
public:
  typedef boost::shared_ptr<UiPlugin> Pointer;
  
  virtual int start(int argc, char *argv[]) = 0;
};

typedef PluginManager<UiPlugin> UiPluginManager;

} /* namespace mru */

#endif /* UI_PLUGIN_HPP */

