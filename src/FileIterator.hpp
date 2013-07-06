#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include "types.hpp"

namespace mru
{

class FileIterator {
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

