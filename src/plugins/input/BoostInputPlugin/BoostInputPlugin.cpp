#include "BoostInputPlugin.hpp"

namespace mru
{

const bfs::directory_iterator
BoostFileIterator::m_end_iterator;

BoostFileIterator::BoostFileIterator(const FilePath &a_directory)
  : m_directory(a_directory)
{
  first();
}

BoostFileIterator::~BoostFileIterator(void)
{ }

FilePath
BoostFileIterator::getFilePath(void) const
{
  assert(!atEnd());
  return bfs::canonical(m_iterator->path());
}

void
BoostFileIterator::first(void)
{
  m_iterator = bfs::directory_iterator(m_directory);
}

bool
BoostFileIterator::next(void)
{
  ++m_iterator;
  return !atEnd();
}

bool
BoostFileIterator::atEnd(void) const
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

FileIterator::Pointer
BoostInputPlugin::getFileIterator(const FilePath &a_path)
{
  try {
    return FileIterator::Pointer(new BoostFileIterator(a_path));
  } catch (bfs::filesystem_error) {
    return FileIterator::Pointer();
  }
}

} /* namespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::BoostInputPlugin)
EXPORT_END

