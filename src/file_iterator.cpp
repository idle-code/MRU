#include "file_iterator.hpp"
#include "glue.hpp"

namespace mru
{

FileIterator::FileIterator(void)
  : m_bfs_iterator()
{ }

FileIterator::FileIterator(const self_type &a_other)
  : m_bfs_iterator(a_other.m_bfs_iterator)
{ }

FileIterator::FileIterator(const filepath_type &a_path)
  : m_bfs_iterator(a_path)
{ }

FileIterator::~FileIterator(void)
{ }

/* ------------------------------------------------------------------------- */

const bfs_iterator_type &
FileIterator::bfs_iterator(void) const
{
  return m_bfs_iterator;
}

filepath_type
FileIterator::directory(void) const
{
  return m_bfs_iterator->path();
}

UnicodeString
FileIterator::filename(void) const
{
  return glue_cast<UnicodeString>(m_bfs_iterator->path().filename());
}

FileIterator::self_type &
FileIterator::operator++(void)
{
  ++m_bfs_iterator;
  return *this;
}

FileIterator::self_type
FileIterator::operator++(int)
{
  self_type tmp(*this);
  ++m_bfs_iterator;
  return tmp;
}

/* ------------------------------------------------------------------------- */

bool
operator==(const FileIterator::self_type &a_a, const FileIterator::self_type &a_b)
{
  return a_a.m_bfs_iterator == a_b.m_bfs_iterator;
}

bool
operator!=(const FileIterator::self_type &a_a, const FileIterator::self_type &a_b)
{
  return a_a.m_bfs_iterator != a_b.m_bfs_iterator;
}

} /* namespace mru */

