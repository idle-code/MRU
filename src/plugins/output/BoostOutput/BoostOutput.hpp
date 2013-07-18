#ifndef BOOST_OUTPUT_HPP
#define BOOST_OUTPUT_HPP

#include "plugins/OutputPlugin.hpp"

namespace mru
{

class BoostOutput : public OutputPlugin {
public:
  PLUGIN_NAME("BoostOutput")
  BoostOutput(void);

  void createDirectory(const FilePath &a_path);
  void removeDirectory(const FilePath &a_path);

  void moveFile(const FilePath &a_source_path, const FilePath &a_destination_path);
  void moveDirectory(const FilePath &a_source_path, const FilePath &a_destination_path);

  bool fileExists(const FilePath &a_path) const;
  bool directoryExists(const FilePath &a_path) const;
};

} /* namespace mru */

#endif /* BOOST_OUTPUT_HPP */

