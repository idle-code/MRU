#include "SortingFileIterator.hpp"

namespace mru
{

FileIterator::Pointer
SortingFileIterator::wrap(FileIterator::Pointer a_iterator, boost::shared_ptr<SortComparator> a_comparator)
{
  return FileIterator::Pointer(new SortingFileIterator(a_iterator, a_comparator));
}

FileIterator::Pointer
SortingFileIterator::wrap(FileIterator::Pointer a_iterator, SortComparator *a_comparator)
{
  return wrap(a_iterator, boost::shared_ptr<SortComparator>(a_comparator));
}

SortingFileIterator::SortingFileIterator(FileIterator::Pointer a_iterator, boost::shared_ptr<SortComparator> &a_comparator)
  : m_iterator(a_iterator), m_comparator(a_comparator)
{
  first();
}

SortingFileIterator::SortingFileIterator(const self_type &a_other)
{
  m_iterator = a_other.m_iterator;
  m_comparator = a_other.m_comparator;
}

SortingFileIterator::~SortingFileIterator(void)
{ }

FilePath
SortingFileIterator::getFilePath(void) const
{
  return FilePath(); //TODO: get filepath from sorted list
}

void
SortingFileIterator::first(void)
{
  //TODO: reset iterator to first element on sorted list
  //generate sorted list?
}

bool
SortingFileIterator::next(void)
{
  return false; //TODO: progress iterator
}

bool
SortingFileIterator::atEnd(void) const
{
  return true; //TODO: check if iterator is at end of sorted list
}

} /* namespace mru */

