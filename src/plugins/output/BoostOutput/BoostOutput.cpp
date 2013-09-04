#include "BoostOutput.hpp"

namespace mru
{

void
BoostOutput::createDirectory(const FilePath &path)
{
  if(exists(path))
    throw OutputPlugin::Exception("Cannot create directory because specified path already exists");
  FilePath parent_dir = path.parent_path(); 
  if(!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPlugin::Exception("Cannot create directory because parent path of specified path doesn't exists");
    else if(!parent_dir.empty())
      bfs::create_directories(path);
  }

  bfs::create_directory(path);
}

void
BoostOutput::removeDirectory(const FilePath &path)
{
  if (!exists(path))
    throw OutputPlugin::Exception("Cannot remove nonexisting directory");

  bfs::remove_all(path);
}

bool
BoostOutput::exists(const FilePath &path) const
{
  if (path.empty())
    return false;
  
  return bfs::exists(path);
}

void
BoostOutput::move(const FilePath &source_path, const FilePath &destination_path)
{
  if (!exists(source_path))
    throw OutputPlugin::Exception("Cannot move because source path doesn't exists");

  FilePath parent_dir = destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPlugin::Exception("Cannot move because parent path of specified path doesn't exists");
    else
      bfs::create_directories(parent_dir);
  }
  if(exists(destination_path)) {
    if (overrideTarget())
      bfs::remove_all(destination_path);
    else
      throw OutputPlugin::Exception("Cannot move because target path exists");
  }
  
  bfs::rename(source_path, destination_path);
}

void
BoostOutput::copy(const FilePath &source_path, const FilePath &destination_path)
{
  if (!exists(source_path))
    throw OutputPlugin::Exception("Cannot move because source path doesn't exists");

  FilePath parent_dir = destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPlugin::Exception("Cannot move because parent path of specified path doesn't exists");
    else
      bfs::create_directories(parent_dir);
  }

  if(exists(destination_path)) {
    if (overrideTarget())
      bfs::remove_all(destination_path);
    else
      throw OutputPlugin::Exception("Cannot move because target path exists");
  }

  bfs::copy(source_path, destination_path);
}

void
BoostOutput::link(const FilePath &source_path, const FilePath &destination_path)
{
  if (!exists(source_path))
    throw OutputPlugin::Exception("Cannot move because source path doesn't exists");

  FilePath parent_dir = destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPlugin::Exception("Cannot move because parent path of specified path doesn't exists");
    else
      bfs::create_directories(parent_dir);
  }
  if(exists(destination_path)) {
    if (overrideTarget())
      bfs::remove_all(destination_path);
    else
      throw OutputPlugin::Exception("Cannot move because target path exists");
  }

  bfs::create_symlink(source_path, destination_path);
}

FilePath
BoostOutput::resolveLink(const FilePath &path) const
{
  if (!exists(path))
    throw OutputPlugin::Exception("Cannot resolve link because specified path doesn't exists");
  if (!bfs::is_symlink(path))
    throw OutputPlugin::Exception("Specified file is not a link");

  return bfs::read_symlink(path);
}

} /* namespace mru */

