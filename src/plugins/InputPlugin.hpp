#ifndef INPUT_PLUGIN_HPP
#define INPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class InputPlugin : public MruPlugin {
public:
  typedef InputPlugin self_type;
public:
  PLUGIN_INTERFACE("InputPlugin")
  InputPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }
  virtual ~InputPlugin(void)
  { }

  virtual FileIterator::Pointer getFileIterator(const FilePath &a_path) = 0;
};

typedef plugin_manager<InputPlugin> InputPluginManager;

} /* namespace mru */

#endif /* INPUT_PLUGIN_HPP */

