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
  : FileIteratorDecorator(a_iterator), m_predicate(a_predicate)
{
  assert(m_predicate);
  first();
}

void
FilteringFileIterator::first(void)
{
  FileIteratorDecorator::first();
  rewind();
}

bool
FilteringFileIterator::next(void)
{
  FileIteratorDecorator::next();
  rewind();
  return !atEnd();
}

void
FilteringFileIterator::rewind(void)
{
  assert(m_predicate);
  while (!atEnd() &&
         !(*m_predicate)(getFilePath()))
  {
    FileIteratorDecorator::next();
  }
}

} /* namespace mru */

