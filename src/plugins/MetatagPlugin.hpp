#ifndef METATAG_PLUGIN_HPP
#define METATAG_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "MetatagBase.hpp"
#include "glue.hpp"

namespace mru
{

class MetatagPlugin : public MruPlugin, public Metatag::MetatagBase {
public:
  MODULE_EXCEPTION(MetatagPlugin, MruPlugin::Exception);

  MetatagPlugin(void)
    : MetatagBase(glue_cast<UnicodeString>(name))
  { }
  
  virtual ~MetatagPlugin(void)
  { }

};

typedef PluginManager<MetatagPlugin> MetatagPluginManager;

} /* namespace mru */

#define METATAG_FACTORY(MetatagClass) \
  class Factory : public PluginManager<MetatagClass>::AbstractPluginFactory> { \
  public: \
    adsf \
  };

#define METATAG_EXPORTS_START \
  extern "C" { \
    void register_metatag_plugins(mru::MetatagPluginManager::Pointer plugin_manager) { \
      assert(plugin_manager);

#define EXPORT_METATAG_PLUGIN_FACTORY(factory) \
      plugin_manager->registerFactory(factory);

#define METATAG_EXPORTS_END \
    } \
  }

#endif /* METATAG_PLUGIN_HPP */

