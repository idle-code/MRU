#ifndef FILTERING_FILE_ITERATOR_HPP
#define FILTERING_FILE_ITERATOR_HPP

#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class FilteringFileIterator : public FileIterator {
public:
  typedef FilteringFileIterator self_type;
  class FilterPredicate {
  public:
    virtual ~FilterPredicate(void) { }
    virtual bool operator()(const FilePath &a_path) = 0;
  };

  static FileIterator::Pointer wrap(FileIterator::Pointer a_iterator, boost::shared_ptr<FilterPredicate> a_predicate);
  static FileIterator::Pointer wrap(FileIterator::Pointer a_iterator, FilterPredicate *a_predicate);
public:
  FilteringFileIterator(FileIterator::Pointer a_iterator, boost::shared_ptr<FilterPredicate> a_predicate);
  FilteringFileIterator(const self_type &a_other);
  ~FilteringFileIterator(void);
  
  FilePath getFilePath(void) const;
  void first(void);
  bool next(void);
  bool atEnd(void) const;

private:
  boost::shared_ptr<FilterPredicate> m_predicate;
  FileIterator::Pointer m_iterator;
  void rewind(void);
};

} /* namespace mru */

#endif /* FILTERING_FILE_ITERATOR_HPP */

