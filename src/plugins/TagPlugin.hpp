#ifndef TAG_PLUGIN_HPP
#define TAG_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "plugin_manager.hpp"
#include "metatag/expression.hpp"

namespace mru
{

class TagPlugin : public MruPlugin {
public:
  typedef TagPlugin self_type;
public:
  PLUGIN_INTERFACE("TagPlugin")
  TagPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }
  
  virtual ~TagPlugin(void)
  { }

};

typedef plugin_manager<TagPlugin> TagPluginManager;

} /* namespace mru */

#endif /* TAG_PLUGIN_HPP */

