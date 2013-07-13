#ifndef BOOST_INPUT_PLUGIN_HPP
#define BOOST_INPUT_PLUGIN_HPP

#include "plugins/InputPlugin.hpp"
#include <list>

namespace mru
{

class BoostInputPlugin : public InputPlugin {
public:
  typedef BoostInputPlugin self_type;
public:
  PLUGIN_NAME("BoostInputPlugin")
  BoostInputPlugin(void);

  FileIterator::Pointer getFileIterator(const FilePath &a_path);
};

} /* namespace mru */

#endif /* BOOST_INPUT_PLUGIN_HPP */

