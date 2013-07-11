#ifndef BOOST_INPUT_PLUGIN_HPP
#define BOOST_INPUT_PLUGIN_HPP

#include "plugins/InputPlugin.hpp"
#include <list>

namespace mru
{

namespace
{

class BoostFileIterator : public FileIterator {
public:
  BoostFileIterator(const FilePath &a_directory);
  ~BoostFileIterator(void);

  FilePath getFilePath(void) const;
  void first(void);
  bool next(void);
  bool atEnd(void) const;
private:
  FilePath m_directory;
  bfs::directory_iterator m_iterator;
  const static bfs::directory_iterator m_end_iterator;
};

} /* anonymous namespace */


class BoostInputPlugin : public InputPlugin {
public:
  typedef BoostInputPlugin self_type;
public:
  PLUGIN_NAME("BoostInputPlugin")
  BoostInputPlugin(void);
  ~BoostInputPlugin(void);

  FileIterator::Pointer getFileIterator(const FilePath &a_path);
};

} /* namespace mru */

#endif /* BOOST_INPUT_PLUGIN_HPP */

