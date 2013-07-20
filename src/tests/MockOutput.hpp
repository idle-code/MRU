#ifndef MOCK_OUTPUT_HPP
#define MOCK_OUTPUT_HPP

#include "OutputPlugin.hpp"
#include <list>
#include <utility>

namespace mru
{

class MockOutput : public OutputPlugin {
public:
  PLUGIN_NAME("MockOutput")
  
  MockOutput(void);

  void createDirectory(const FilePath &a_path);
  void removeDirectory(const FilePath &a_path);
  
  bool exists(const FilePath &a_path) const;

  void move(const FilePath &a_source_path, const FilePath &a_destination_path);
  void copy(const FilePath &a_source_path, const FilePath &a_destination_path);
  void link(const FilePath &a_source_path, const FilePath &a_destination_path);
  FilePath resolveLink(const FilePath &a_path) const;

private:
  typedef enum { File, Directory } PathKind;
  typedef std::list< std::pair<FilePath, PathKind> > FileList;
  typedef std::list< std::pair<FilePath, FilePath> > LinkList;
  FileList m_file_list;
  LinkList m_link_list;
private:
  FileList::iterator getIterator(const FilePath &a_path);
  FileList::const_iterator getIterator(const FilePath &a_path) const;
  LinkList::iterator getLinkIterator(const FilePath &a_path);
  LinkList::const_iterator getLinkIterator(const FilePath &a_path) const;

public:
  void createFile(const FilePath &a_path); // for testing purposes
};

} /* namespace mru */

#endif /* MOCK_OUTPUT_HPP */

