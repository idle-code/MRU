#include "BoostInput.hpp"
#include "FilteringFileIterator.hpp"

namespace mru
{

template<typename IteratorType>
class BoostFileIterator : public FileIterator {
public:
  BoostFileIterator(const FilePath &a_directory)
    : m_directory(a_directory)
  {
    first();
  }

  FilePath getFilePath(void) const
  {
    assert(!atEnd());
    return bfs::canonical(m_iterator->path());
  }

  void first(void)
  {
    m_iterator = IteratorType(m_directory);
  }

  bool next(void)
  {
    ++m_iterator;
    return !atEnd();
  }

  bool atEnd(void) const
  {
    return m_iterator == m_end_iterator;
  }
private:
  FilePath m_directory;
  IteratorType m_iterator;
  const static IteratorType m_end_iterator;
};

template<typename IteratorType>
const IteratorType
BoostFileIterator<IteratorType>::m_end_iterator;

/* ------------------------------------------------------------------------- */

BoostInput::BoostInput(void)
  : InputPlugin(static_implementation_name())
{ }

namespace
{

struct FilesOnlyFilter : public FilteringFileIterator::FilterPredicate
{
  bool
  operator()(const FilePath &a_path)
  {
    return bfs::is_regular(a_path);
  }
};

struct DirectoriesOnlyFilter : public FilteringFileIterator::FilterPredicate
{
  bool
  operator()(const FilePath &a_path)
  {
    return bfs::is_directory(a_path);
  }
};

} /* anonymous namespace */

FileIterator::Pointer
BoostInput::getFileIterator(const FilePath &a_path)
{
  if(!includeFiles() && !includeDirectories())
    throw InputPluginException(std::string("Bad input configuration - no files will ever met specified conditions"));
  
  try {
    FileIterator::Pointer file_iterator;
    if(searchRecursively())
      file_iterator = FileIterator::Pointer(new BoostFileIterator<bfs::recursive_directory_iterator>(a_path));
    else
      file_iterator = FileIterator::Pointer(new BoostFileIterator<bfs::directory_iterator>(a_path));

    if(includeFiles() && !includeDirectories())
      file_iterator = FilteringFileIterator::wrap(file_iterator, new FilesOnlyFilter());
    else if(!includeFiles() && includeDirectories())
      file_iterator = FilteringFileIterator::wrap(file_iterator, new DirectoriesOnlyFilter());
    //else include both    
    return file_iterator;
  } catch (bfs::filesystem_error fe) {
    throw InputPluginException(std::string(fe.what()));
  }
}

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::BoostInput)
EXPORT_END

