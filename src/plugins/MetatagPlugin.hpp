#ifndef METATAG_PLUGIN_HPP
#define METATAG_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "plugin_manager.hpp"
#include "Metatag.hpp"
#include "glue.hpp"

namespace mru
{

class MetatagPlugin : public MruPlugin, public Metatag {
public:
  typedef MetatagPlugin self_type;
public:
  PLUGIN_INTERFACE("MetatagPlugin")
  MetatagPlugin(const name_type &name)
    : MruPlugin(static_interface_name(), name), Metatag(glue_cast<UnicodeString>(name))
  { }
  
  virtual ~MetatagPlugin(void)
  { }

};

typedef plugin_manager<MetatagPlugin> MetatagPluginManager;

} /* namespace mru */

#endif /* METATAG_PLUGIN_HPP */

