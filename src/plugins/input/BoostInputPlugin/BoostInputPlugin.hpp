#ifndef BOOST_INPUT_PLUGIN_HPP
#define BOOST_INPUT_PLUGIN_HPP

#include "plugins/InputPlugin.hpp"

namespace mru
{

class BoostInputPlugin : public InputPlugin {
public:
  typedef BoostInputPlugin self_type;
public:
  PLUGIN_NAME("BoostInputPlugin")
  BoostInputPlugin(void);
  ~BoostInputPlugin(void);

  FileIterator* getFileIterator(const FilePath &a_path);

private:
  bfs::directory_iterator m_iterator;
};

} /* namespace mru */

#endif /* BOOST_INPUT_PLUGIN_HPP */

