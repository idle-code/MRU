#include "FilteringFileIterator.hpp"

namespace mru
{

FileIterator::Pointer
FilteringFileIterator::wrap(FileIterator::Pointer a_iterator, boost::shared_ptr<FilterPredicate> a_predicate)
{
  return FileIterator::Pointer(new FilteringFileIterator(a_iterator, a_predicate));
}

FileIterator::Pointer
FilteringFileIterator::wrap(FileIterator::Pointer a_iterator, FilterPredicate *a_predicate)
{
  return wrap(a_iterator, boost::shared_ptr<FilterPredicate>(a_predicate));
}

/* ------------------------------------------------------------------------- */

FilteringFileIterator::FilteringFileIterator(FileIterator::Pointer a_iterator, boost::shared_ptr<FilterPredicate> a_predicate)
  : m_iterator(a_iterator), m_predicate(a_predicate)
{
  assert(m_iterator);
  assert(m_predicate);
  first();
}

FilteringFileIterator::FilteringFileIterator(const self_type &a_other)
{
  m_iterator = a_other.m_iterator;
  m_predicate = a_other.m_predicate;
  assert(m_iterator);
  assert(m_predicate);
}

FilteringFileIterator::~FilteringFileIterator(void)
{ }

FilePath
FilteringFileIterator::getFilePath(void) const
{
  assert(m_iterator);
  return m_iterator->getFilePath();
}

void
FilteringFileIterator::first(void)
{
  assert(m_iterator);
  m_iterator->first();
  rewind();
}

bool
FilteringFileIterator::next(void)
{
  assert(m_iterator);
  m_iterator->next();
  rewind();
  return !m_iterator->atEnd();
}

bool
FilteringFileIterator::atEnd(void) const
{
  assert(m_iterator);
  return m_iterator->atEnd();
}

void
FilteringFileIterator::rewind(void)
{
  assert(m_iterator);
  assert(m_predicate);

  while (!m_iterator->atEnd() &&
         !(*m_predicate)(m_iterator->getFilePath()))
  {
    m_iterator->next();
  }
}

} /* namespace mru */

