#ifndef MOCK_OUTPUT_HPP
#define MOCK_OUTPUT_HPP

#include "OutputPlugin.hpp"
#include <list>
#include <utility>

namespace mru
{

class MockOutput : public OutputPlugin {
public:
  typedef enum { File, Directory } PathKind;
  typedef std::list< std::pair<FilePath, PathKind> > FileList;
public:
  PLUGIN_NAME("MockOutput")
  
  MockOutput(void);

  void createDirectory(const FilePath &a_path);
  void removeDirectory(const FilePath &a_path);
  
  void moveFile(const FilePath &a_source_path, const FilePath &a_destination_path);
  void moveDirectory(const FilePath &a_source_path, const FilePath &a_destination_path);

  bool fileExists(const FilePath &a_path) const;
  bool directoryExists(const FilePath &a_path) const;
public:
  void move(const FilePath &a_source_path, const FilePath &a_destination_path);
  void createFile(const FilePath &a_path); // for testing purposes

private:
  FileList m_file_list;
};

} /* namespace mru */

#endif /* MOCK_OUTPUT_HPP */

