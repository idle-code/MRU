#include "BoostOutput.hpp"

namespace mru
{

BoostOutput::BoostOutput(void)
  : OutputPlugin(static_implementation_name())
{ }

void
BoostOutput::createDirectory(const FilePath &a_path)
{
  if(exists(a_path))
    throw OutputPluginException("Cannot create directory because specified path already exists");
  FilePath parent_dir = a_path.parent_path(); 
  if(!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot create directory because parent path of specified path doesn't exists");
    else if(!parent_dir.empty())
      bfs::create_directories(a_path);
  }

  bfs::create_directory(a_path);
}

void
BoostOutput::removeDirectory(const FilePath &a_path)
{
  if (!exists(a_path))
    throw OutputPluginException("Cannot remove nonexisting directory");

  bfs::remove_all(a_path);
}

bool
BoostOutput::exists(const FilePath &a_path) const
{
  if (a_path.empty())
    return false;
  
  return bfs::exists(a_path);
}

void
BoostOutput::move(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!exists(a_source_path))
    throw OutputPluginException("Cannot move because source path doesn't exists");

  FilePath parent_dir = a_destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      bfs::create_directories(parent_dir);
  }
  if(exists(a_destination_path)) {
    if (overwriteTarget())
      bfs::remove_all(a_destination_path);
    else
      throw OutputPluginException("Cannot move because target path exists");
  }
  
  bfs::rename(a_source_path, a_destination_path);
}

void
BoostOutput::copy(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!exists(a_source_path))
    throw OutputPluginException("Cannot move because source path doesn't exists");

  FilePath parent_dir = a_destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      bfs::create_directories(parent_dir);
  }

  if(exists(a_destination_path)) {
    if (overwriteTarget())
      bfs::remove_all(a_destination_path);
    else
      throw OutputPluginException("Cannot move because target path exists");
  }

  bfs::copy(a_source_path, a_destination_path);
}

void
BoostOutput::link(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!exists(a_source_path))
    throw OutputPluginException("Cannot move because source path doesn't exists");

  FilePath parent_dir = a_destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      bfs::create_directories(parent_dir);
  }
  if(exists(a_destination_path)) {
    if (overwriteTarget())
      bfs::remove_all(a_destination_path);
    else
      throw OutputPluginException("Cannot move because target path exists");
  }

  bfs::create_symlink(a_source_path, a_destination_path);
}

FilePath
BoostOutput::resolveLink(const FilePath &a_path) const
{
  if (!exists(a_path))
    throw OutputPluginException("Cannot resolve link because specified path doesn't exists");
  if (!bfs::is_symlink(a_path))
    throw OutputPluginException("Specified file is not a link");

  return bfs::read_symlink(a_path);
}

} /* namespace mru */

