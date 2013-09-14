#ifndef MRUPLUGIN_HPP
#define MRUPLUGIN_HPP

#include "PluginManager.hpp"
#include <cassert>

namespace mru {

// forward declaration:
class MruCore;

class MruPlugin {
public:
  MODULE_EXCEPTION(MruPlugin, MruException);
public:
  MruPlugin(void);
  virtual ~MruPlugin(void);
  
  virtual bool Init(MruCore *mru_core);

  virtual MruCore* getCore(void);

private:
  MruCore *core;
};

} /* namespace mru */

#define EXPORT_PLUGIN_FACTORY(PLUGIN_INTERFACE, PLUGIN_TYPE) \
  extern "C" { \
    void register##PLUGIN_INTERFACE##Factory (mru::PLUGIN_INTERFACE::Manager::Pointer plugin_manager) { \
      assert(plugin_manager); \
      plugin_manager->registerFactory(PLUGIN_TYPE::Factory::createRaw(#PLUGIN_TYPE)); \
    } \
  }

  //void unregister##PluginType##Factory (

#endif /* MRUPLUGIN_HPP */

