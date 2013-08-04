#include "FilteringFileIterator.hpp"

namespace mru
{

FileIterator::Pointer
FilteringFileIterator::wrap(FileIterator::Pointer iterator, boost::shared_ptr<FilterPredicate> predicate)
{
  return FileIterator::Pointer(new FilteringFileIterator(iterator, predicate));
}

FileIterator::Pointer
FilteringFileIterator::wrap(FileIterator::Pointer iterator, FilterPredicate *predicate)
{
  return wrap(iterator, boost::shared_ptr<FilterPredicate>(predicate));
}

/* ------------------------------------------------------------------------- */

FilteringFileIterator::FilteringFileIterator(FileIterator::Pointer iterator, boost::shared_ptr<FilterPredicate> predicate)
  : FileIteratorDecorator(iterator), predicate(predicate)
{
  assert(predicate);
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
  assert(predicate);
  while (!atEnd() &&
         !(*predicate)(getCurrent()))
  {
    FileIteratorDecorator::next();
  }
}

} /* namespace mru */

