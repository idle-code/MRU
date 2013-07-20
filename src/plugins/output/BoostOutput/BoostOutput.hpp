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

  bool exists(const FilePath &a_path) const;

  void move(const FilePath &a_source_path, const FilePath &a_destination_path);
  void copy(const FilePath &a_source_path, const FilePath &a_destination_path);
  void link(const FilePath &a_source_path, const FilePath &a_destination_path);
  FilePath resolveLink(const FilePath &a_path) const;
};

} /* namespace mru */

#endif /* BOOST_OUTPUT_HPP */

