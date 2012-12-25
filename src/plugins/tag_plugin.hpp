#ifndef TAG_PLUGIN_HPP
#define TAG_PLUGIN_HPP

#include <plugin_manager.hpp>

namespace mru
{

class TagPlugin : public plugin<TagPlugin> {
public:
  typedef TagPlugin self_type;
public:
  PLUGIN_INTERFACE("TagPlugin")
  TagPlugin(const name_type &a_name)
    : plugin<TagPlugin>(static_interface_name(), a_name)
  { }
  
  virtual ~TagPlugin(void)
  { }

};

typedef plugin_manager<TagPlugin> TagPluginManager;

} /* namespace mru */

#endif /* TAG_PLUGIN_HPP */

