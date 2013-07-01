#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include "types.hpp"
#include <unicode/regex.h>

namespace mru
{

class MruCore; // forward declaration

class FileIterator {
public:
  typedef FileIterator self_type;
  friend class MruCore;
public:
  FileIterator(void); // creates end() iterator
  FileIterator(const self_type &a_other); //FIXME: temporary
  //FileIterator(const filepath_type &a_path); // creates begin() iterator
  //FileIterator(const UnicodeString &a_path, const UnicodeString &a_metatag_expr = "%NAME()"); //TODO
  ~FileIterator(void);

  const UnicodeString& filter_expression(void) const;
  const UnicodeString& filter_expression(const UnicodeString &a_expr);
  
  UnicodeString directory(void) const;
  UnicodeString filename(void) const;
  UnicodeString bare_filename(void) const;
  UnicodeString absolute_filename(void) const;
  UnicodeString absolute_directory(void) const;
  UnicodeString base_directory(void) const;

  void set_new_filename(const UnicodeString &a_filename);
  void set_new_directory(const UnicodeString &a_directory);

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
  FileIterator(const filepath_type &a_path, bool a_directory, bool a_file, const UnicodeString &a_filter);

  void progress_if_needed(void);
private:
  bool m_include_directories;
  bool m_include_files;
  UnicodeString m_filter;
};

} /* namespace mru */

#endif /* FILE_ITERATOR_HPP */

