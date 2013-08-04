#include "MockFileIterator.hpp"

namespace mru
{

MockFileIterator::MockFileIterator(const std::list<FilePath> &list)
  : file_list(list), iterator(file_list.begin()), end_iterator(file_list.end())
{
  first(); // not really needed
}

FilePath
MockFileIterator::getCurrent(void) const
{
  assert(!atEnd());
  return *iterator;
}

void
MockFileIterator::first(void)
{
  iterator = file_list.begin();
}

bool
MockFileIterator::next(void)
{
  ++iterator;
  return !atEnd();
}

bool
MockFileIterator::atEnd(void) const
{
  return iterator == end_iterator;
}

} /* namespace mru */

