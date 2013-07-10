#ifndef BOOST_INPUT_PLUGIN_HPP
#define BOOST_INPUT_PLUGIN_HPP

#include "plugins/InputPlugin.hpp"

namespace mru
{

namespace
{

template<typename ProgressPredicate>
class BoostFileIterator : public FileIterator {
public:
  BoostFileIterator(const FilePath &a_directory, const ProgressPredicate &a_predicate);
  ~BoostFileIterator(void);

  FilePath getFilePath(void) const;

  void setNewFilePath(const FilePath &a_filename);
  FilePath getNewFilePath(void) const;

  bool next(void);
  bool atEnd(void) const;
private:
  ProgressPredicate m_predicate;
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

  FileIterator* getFileIterator(const FilePath &a_path, const FileIterator::SortComparator &a_sort_comparator);

private:
  bfs::directory_iterator m_iterator;
};

} /* namespace mru */

#endif /* BOOST_INPUT_PLUGIN_HPP */

