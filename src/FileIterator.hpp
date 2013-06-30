#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include "types.hpp"

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
  
  UnicodeString directory(void) const; //!< returns path to relative root directory of created iterator
  UnicodeString filename(void) const; //!< returns sole filename targeted by iterator
  UnicodeString bare_filename(void) const; //!< returns sole filename targeted by iterator
  UnicodeString base_filename(void) const; //!< returns fully-qualified, absolute filename of targeted file
  UnicodeString base_directory(void) const; //!< return absolute directory of targeted file

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
  FileIterator(const filepath_type &a_path, bool a_directory, bool a_file);

  void progress_to_next_directory(void);
  void progress_to_next_file(void);
private:
  bool m_include_directories;
  bool m_include_files;
};

} /* namespace mru */

#endif /* FILE_ITERATOR_HPP */

