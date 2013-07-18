#include "BoostOutput.hpp"

namespace mru
{

BoostOutput::BoostOutput(void)
  : OutputPlugin(static_implementation_name())
{ }

void
BoostOutput::createDirectory(const FilePath &a_path)
{
  //TODO
}

void
BoostOutput::removeDirectory(const FilePath &a_path)
{
  //TODO
}

void
BoostOutput::moveFile(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  //TODO

}

void
BoostOutput::moveDirectory(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  //TODO
}


bool
BoostOutput::fileExists(const FilePath &a_path) const
{
  return bfs::exists(a_path) && bfs::is_regular(a_path);
}

bool
BoostOutput::directoryExists(const FilePath &a_path) const
{
  return bfs::exists(a_path) && bfs::is_directory(a_path);
}


} /* namespace mru */

