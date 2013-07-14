#ifndef BOOST_OUTPUT_HPP
#define BOOST_OUTPUT_HPP

#include "plugins/OutputPlugin.hpp"

namespace mru
{

class BoostOutput : public OutputPlugin {
public:
  typedef BoostOutput self_type;
public:
  PLUGIN_NAME("BoostOutput")
  BoostOutput(void);

  bool rename(const FilePath &a_name, const FilePath &a_new_name);
};

} /* namespace mru */

#endif /* BOOST_OUTPUT_HPP */

