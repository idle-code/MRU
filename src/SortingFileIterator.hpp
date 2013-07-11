#ifndef SORTING_FILE_ITERATOR_HPP
#define SORTING_FILE_ITERATOR_HPP

#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class SortingFileIterator : public FileIterator {
public:
  typedef SortingFileIterator self_type;
  class SortComparator {
  public:
    virtual ~SortComparator(void) { }
    virtual int operator()(const FilePath &a_path_a, const FilePath &a_path_b)
    {
      return a_path_a < a_path_b;
    } 
  };

  static FileIterator::Pointer wrap(FileIterator::Pointer a_iterator, boost::shared_ptr<SortComparator> a_comparator);
  static FileIterator::Pointer wrap(FileIterator::Pointer a_iterator, SortComparator *a_comparator);
public:
  SortingFileIterator(FileIterator::Pointer a_iterator, boost::shared_ptr<SortComparator> &a_comparator);
  SortingFileIterator(const self_type &a_other);
  ~SortingFileIterator(void);
  
  FilePath getFilePath(void) const;
  void first(void);
  bool next(void);
  bool atEnd(void) const;

private:
  boost::shared_ptr<SortComparator> m_comparator;
  FileIterator::Pointer m_iterator;
  std::list<FilePath> m_sorted_list;
};

} /* namespace mru */

#endif /* SORTING_FILE_ITERATOR_HPP */

