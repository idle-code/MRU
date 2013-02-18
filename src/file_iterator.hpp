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
  const UnicodeString& filter_expression(const UnicodeString &a_metatag_expr);
  
  const bfs_iterator_type& bfs_iterator(void) const;
  
  filepath_type directory(void) const;
  UnicodeString filename(void) const; 

  //UnicodeString operator*(void) const;
  self_type& operator++(void);
  self_type  operator++(int);

  friend bool operator==(const self_type &a_a, const self_type &a_b); 
  friend bool operator!=(const self_type &a_a, const self_type &a_b); 
protected:
  bfs_iterator_type m_bfs_iterator;
};

} /* namespace mru */

#endif /* FILE_ITERATOR_HPP */

