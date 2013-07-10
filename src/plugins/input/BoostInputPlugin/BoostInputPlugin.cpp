#include "BoostInputPlugin.hpp"

namespace mru
{

template<typename ProgressPredicate>
const bfs::directory_iterator
BoostFileIterator<ProgressPredicate>::m_end_iterator;

template<typename ProgressPredicate>
BoostFileIterator<ProgressPredicate>::BoostFileIterator(const FilePath &a_directory, const ProgressPredicate &a_predicate)
  : m_iterator(a_directory), m_predicate(a_predicate)
{
  while(!atEnd() && !m_predicate(m_iterator->path()))
    ++m_iterator;
}

template<typename ProgressPredicate>
BoostFileIterator<ProgressPredicate>::~BoostFileIterator(void)
{ }


template<typename ProgressPredicate>
FilePath
BoostFileIterator<ProgressPredicate>::getFilePath(void) const
{
  assert(!atEnd());
  return bfs::canonical(m_iterator->path());
}


template<typename ProgressPredicate>
void
BoostFileIterator<ProgressPredicate>::setNewFilePath(const FilePath &a_filename)
{
  assert(!atEnd());
  
}

template<typename ProgressPredicate>
FilePath
BoostFileIterator<ProgressPredicate>::getNewFilePath(void) const
{
  assert(!atEnd());

  return FilePath();
}


template<typename ProgressPredicate>
bool
BoostFileIterator<ProgressPredicate>::next(void)
{
  ++m_iterator;
  while(!atEnd() && !m_predicate(m_iterator->path()))
    ++m_iterator;
  if(atEnd())
    return false;
  return true;
}

template<typename ProgressPredicate>
bool
BoostFileIterator<ProgressPredicate>::atEnd(void) const
{
  return m_iterator == m_end_iterator;
}

/* ------------------------------------------------------------------------- */

BoostInputPlugin::BoostInputPlugin(void)
  : InputPlugin(static_implementation_name())
{
  FO("BoostInputPlugin::BoostInputPlugin(void)");

}

BoostInputPlugin::~BoostInputPlugin(void)
{
  FO("BoostInputPlugin::~BoostInputPlugin(void)");
}

namespace {

class SimplePredicate : public FileIterator::FilePredicate {
public:
  SimplePredicate(bool a_files, bool a_directories);
  bool operator()(const FilePath &a_argument);
protected:
  bool m_files, m_directories;
};

SimplePredicate::SimplePredicate(bool a_files, bool a_directories)
  : m_files(a_files), m_directories(a_directories)
{ }

bool
SimplePredicate::operator()(const FilePath &a_argument)
{
  //FO("Predicate::operator()(const FilePath &a_argument)");
  VAL(a_argument);
  VAL(m_files);
  VAL(m_directories);
  VAL(bfs::is_regular(a_argument));
  VAL(bfs::is_directory(a_argument));
  int result = 0;
  result += (m_files && bfs::is_regular(a_argument));
  result += (m_directories && bfs::is_directory(a_argument));
  //if(!m_files && bfs::is_regular(a_argument))
  //  return true;
  //if(!m_directories && bfs::is_directory(a_argument))
  //  return false;
  VAL(result);
  return result > 0;
}

} /* anonymous namespace */

FileIterator *
BoostInputPlugin::getFileIterator(const FilePath &a_path,  const FileIterator::SortComparator &a_sort_comparator)
{
  return new BoostFileIterator<SimplePredicate>(a_path, SimplePredicate(true, false));
}

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::BoostInputPlugin)
EXPORT_END

