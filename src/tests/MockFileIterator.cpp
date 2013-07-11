#include "MockFileIterator.hpp"

namespace mru
{

MockFileIterator::MockFileIterator(const std::list<FilePath> &a_list)
  : m_file_list(a_list), m_iterator(m_file_list.begin()), m_end_iterator(m_file_list.end())
{
  first(); // not really needed
}

FilePath
MockFileIterator::getFilePath(void) const
{
  assert(!atEnd());
  return *m_iterator;
}

void
MockFileIterator::first(void)
{
  m_iterator = m_file_list.begin();
}

bool
MockFileIterator::next(void)
{
  ++m_iterator;
  return !atEnd();
}

bool
MockFileIterator::atEnd(void) const
{
  return m_iterator == m_end_iterator;
}

} /* namespace mru */

