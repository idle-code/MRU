#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include "types.hpp"

namespace mru
{

class FileIterator {
public:
  typedef FileIterator self_type;
public:
  FileIterator(void); // creates end() iterator
  FileIterator(const self_type &a_other); //FIXME: temporary
  FileIterator(const filepath_type &a_path); // creates begin() iterator
  //FileIterator(const UnicodeString &a_path, const UnicodeString &a_metatag_expr = "%NAME()"); //TODO
  ~FileIterator(void);

  const UnicodeString& filter_expression(void) const;
  const UnicodeString& filter_expression(const UnicodeString &a_expr);
  
  UnicodeString directory(void) const; //!< returns path to relative root directory of created iterator
  UnicodeString filename(void) const; //!< returns sole filename targeted by iterator
  UnicodeString base_filename(void) const; //!< returns fully-qualified, absolute filename of targeted file
  UnicodeString base_directory(void) const; //!< return absolute directory of targeted file

  //UnicodeString operator*(void) const;
  self_type& operator++(void);
  self_type  operator++(int);

  friend bool operator==(const self_type &a_a, const self_type &a_b); 
  friend bool operator!=(const self_type &a_a, const self_type &a_b); 
protected:
  bfs::recursive_directory_iterator m_bfs_iterator;
  bfs::path m_base_path;
protected:
  const bfs::recursive_directory_iterator& bfs_iterator(void) const;
};

} /* namespace mru */

#endif /* FILE_ITERATOR_HPP */

