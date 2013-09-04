#ifndef MOCK_OUTPUT_HPP
#define MOCK_OUTPUT_HPP

#include "OutputPlugin.hpp"
#include <list>
#include <utility>

namespace mru
{

class MockOutput : public OutputPlugin {
public:
  void createDirectory(const FilePath &path);
  void removeDirectory(const FilePath &path);
  
  bool exists(const FilePath &path) const;

  void move(const FilePath &source_path, const FilePath &destination_path);
  void copy(const FilePath &source_path, const FilePath &destination_path);
  void link(const FilePath &source_path, const FilePath &destination_path);
  FilePath resolveLink(const FilePath &path) const;

private:
  typedef enum { File, Directory } PathKind;
  typedef std::list< std::pair<FilePath, PathKind> > FileList;
  typedef std::list< std::pair<FilePath, FilePath> > LinkList;
  FileList file_list;
  LinkList link_list;
private:
  FileList::iterator getIterator(const FilePath &path);
  FileList::const_iterator getIterator(const FilePath &path) const;
  LinkList::iterator getLinkIterator(const FilePath &path);
  LinkList::const_iterator getLinkIterator(const FilePath &path) const;

public:
  void createFile(const FilePath &path); // for testing purposes
};

} /* namespace mru */

#endif /* MOCK_OUTPUT_HPP */

