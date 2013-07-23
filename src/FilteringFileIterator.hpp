#ifndef FILTERING_FILE_ITERATOR_HPP
#define FILTERING_FILE_ITERATOR_HPP

#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class FilteringFileIterator : public FileIteratorDecorator {
public:
  typedef FilteringFileIterator self_type;
  class FilterPredicate {
  public:
    virtual ~FilterPredicate(void) { }
    virtual bool operator()(const FilePath &path) = 0;
  };

  static FileIterator::Pointer wrap(FileIterator::Pointer iterator, boost::shared_ptr<FilterPredicate> predicate);
  static FileIterator::Pointer wrap(FileIterator::Pointer iterator, FilterPredicate *predicate);
public:
  FilteringFileIterator(FileIterator::Pointer iterator, boost::shared_ptr<FilterPredicate> predicate);
  
  void first(void);
  bool next(void);

private:
  boost::shared_ptr<FilterPredicate> predicate;
  void rewind(void);
};

} /* namespace mru */

#endif /* FILTERING_FILE_ITERATOR_HPP */

