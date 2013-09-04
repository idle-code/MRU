#ifndef BOOST_OUTPUT_HPP
#define BOOST_OUTPUT_HPP

#include "plugins/OutputPlugin.hpp"

namespace mru
{

class BoostOutput : public OutputPlugin {
public:
  void createDirectory(const FilePath &path);
  void removeDirectory(const FilePath &path);

  bool exists(const FilePath &path) const;

  void move(const FilePath &source_path, const FilePath &destination_path);
  void copy(const FilePath &source_path, const FilePath &destination_path);
  void link(const FilePath &source_path, const FilePath &destination_path);
  FilePath resolveLink(const FilePath &path) const;
};

} /* namespace mru */

#endif /* BOOST_OUTPUT_HPP */

