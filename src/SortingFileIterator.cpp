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
  : FileIteratorDecorator(a_iterator), m_comparator(a_comparator)
{
  assert(a_comparator);
  first();
}

FilePath
SortingFileIterator::getCurrent(void) const
{
  assert(!atEnd());
  return *m_iterator;
}

namespace 
{

struct SortingFunctor { //IMPROVE: if SortingComparator class could be copied, this could be removed
  SortingFunctor(boost::shared_ptr<SortingFileIterator::SortComparator> a_comparator)
    : m_comparator(a_comparator)
  { }

  bool operator()(const FilePath &a_path_a, const FilePath &a_path_b)
  {
    return (*m_comparator)(a_path_a, a_path_b);
  }
  boost::shared_ptr<SortingFileIterator::SortComparator> m_comparator;
};

} /* anonymous namespace */

void
SortingFileIterator::first(void)
{
  assert(m_comparator);
  m_sorted_list.clear();

  FileIteratorDecorator::first(); 
  for(; !FileIteratorDecorator::atEnd(); FileIteratorDecorator::next()) {
    m_sorted_list.push_back(FileIteratorDecorator::getCurrent());
  }

  m_sorted_list.sort(SortingFunctor(m_comparator));

  m_iterator = m_sorted_list.begin();
  m_end_iterator = m_sorted_list.end();
}

bool
SortingFileIterator::next(void)
{
  assert(!atEnd());
  ++m_iterator;
  return !atEnd();
}

bool
SortingFileIterator::atEnd(void) const
{
  return m_iterator == m_end_iterator;
}

} /* namespace mru */

