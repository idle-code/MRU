#ifndef MOCK_FILE_ITERATOR_HPP
#define MOCK_FILE_ITERATOR_HPP

#include "FileIterator.hpp"
#include <list>

namespace mru
{

class MockFileIterator : public FileIterator {
public:
  typedef MockFileIterator self_type;
public:
  MockFileIterator(const std::list<FilePath> &a_list);

  FilePath getFilePath(void) const;
  void first(void);
  bool next(void);
  bool atEnd(void) const;

private:
  std::list<FilePath> m_file_list;
  std::list<FilePath>::iterator m_iterator;
  const std::list<FilePath>::const_iterator m_end_iterator;
};

} /* namespace mru */

#endif /* MOCK_FILE_ITERATOR_HPP */

