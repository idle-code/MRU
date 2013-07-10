#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include "types.hpp"

namespace mru
{

class FileIterator {
public:
  class FilePredicate {
  public:
    virtual ~FilePredicate(void) { }
    virtual bool operator()(const FilePath &a_path) = 0;
  };

  class SortComparator {
  public:
    virtual ~SortComparator(void) { }
    virtual int operator()(const FilePath &a_path_a, const FilePath &a_path_b)
    {
      return a_path_a < a_path_b;
    } 
  };
public:
  virtual ~FileIterator(void);

  virtual FilePath getFilePath(void) const = 0;

  virtual void setNewFilePath(const FilePath &a_filename) = 0;
  virtual FilePath getNewFilePath(void) const = 0;

  virtual bool next(void) = 0;
  virtual bool atEnd(void) const = 0;
};

} /* namespace mru */

#endif /* FILE_ITERATOR_HPP */

