#ifndef OUTPUT_PLIGIN_HPP
#define OUTPUT_PLIGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "plugin_manager.hpp"

namespace mru
{

class OutputPlugin : public MruPlugin {
public:
  typedef OutputPlugin self_type;
public:
  PLUGIN_INTERFACE("OutputPlugin")
  OutputPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }
  virtual ~OutputPlugin(void)
  { }

  virtual bool change_directory(const filepath_type &a_path) = 0;
  virtual bool rename(const filepath_type &a_name, const filepath_type &a_new_name) = 0;
  //virtual bool move(const filepath_type &a_location, const filepath_type &a_new_location) = 0;
};

typedef plugin_manager<OutputPlugin> OutputPluginManager;

} /* namespace mru */

#endif /* OUTPUT_PLIGIN_HPP */

