#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include "types.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class FileIterator {
public:
  typedef boost::shared_ptr<FileIterator> Pointer;
public:
  virtual ~FileIterator(void);

  virtual FilePath getFilePath(void) const = 0;
  virtual void first(void) = 0;
  virtual bool next(void) = 0;
  virtual bool atEnd(void) const = 0;
};

/* ------------------------------------------------------------------------- */

class FileIteratorDecorator : public FileIterator {
public:
  typedef FileIteratorDecorator self_type;
public:
  FileIteratorDecorator(FileIterator::Pointer instance);

  FilePath getFilePath(void) const;
  void first(void);
  bool next(void);
  bool atEnd(void) const;
private:
  FileIterator::Pointer instance;
};

} /* namespace mru */

#endif /* FILE_ITERATOR_HPP */

