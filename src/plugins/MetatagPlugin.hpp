#ifndef METATAG_PLUGIN_HPP
#define METATAG_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "MetatagBase.hpp"
#include "glue.hpp"

namespace mru
{

class MetatagPlugin : public MruPlugin, public Metatag::MetatagBase {
public:
  typedef PluginManager<MetatagPlugin> Manager;
  typedef DynamicPluginManager<MetatagPlugin> DynamicManager;
  static const char* getRegisterFunctionName(void) { return "registerMetatagFactory"; }
  MODULE_EXCEPTION(MetatagPlugin, MruPlugin::Exception);

  MetatagPlugin(void)
  { }
  
  virtual ~MetatagPlugin(void)
  { }

};

} /* namespace mru */

#define METATAG_EXPORTS_START \
  extern "C" { \
    void registerMetatagFactory(mru::MetatagPlugin::Manager *plugin_manager) { \
      assert(plugin_manager);

#define EXPORT_METATAG_PLUGIN_FACTORY(PLUGIN_TYPE, TAG_NAME) \
      plugin_manager->registerFactory(PLUGIN_TYPE::Factory::allocateFactory(TAG_NAME), &PLUGIN_TYPE::Factory::destroyFactory); \

#define METATAG_EXPORTS_END \
    } \
  }

#endif /* METATAG_PLUGIN_HPP */

