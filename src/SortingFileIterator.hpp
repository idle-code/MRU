#ifndef SORTING_FILE_ITERATOR_HPP
#define SORTING_FILE_ITERATOR_HPP

#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class SortingFileIterator : public FileIteratorDecorator {
public:
  typedef SortingFileIterator self_type;
  class SortComparator {
  public:
    virtual ~SortComparator(void) { }
    virtual int operator()(const FilePath &a_path_a, const FilePath &a_path_b) = 0;
  };

  static FileIterator::Pointer wrap(FileIterator::Pointer a_iterator, boost::shared_ptr<SortComparator> a_comparator);
  static FileIterator::Pointer wrap(FileIterator::Pointer a_iterator, SortComparator *a_comparator);
public:
  SortingFileIterator(FileIterator::Pointer a_iterator, boost::shared_ptr<SortComparator> &a_comparator);

  FilePath getCurrent(void) const;
  void first(void);
  bool next(void);
  bool atEnd(void) const;

private:
  boost::shared_ptr<SortComparator> m_comparator;
  std::list<FilePath> m_sorted_list;
  std::list<FilePath>::iterator m_iterator;
  std::list<FilePath>::const_iterator m_end_iterator;
};

} /* namespace mru */

#endif /* SORTING_FILE_ITERATOR_HPP */

