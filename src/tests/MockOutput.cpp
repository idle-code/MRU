#include "MockOutput.hpp"

namespace mru
{

MockOutput::MockOutput(void)
  : OutputPlugin(static_implementation_name()),
    file_list()
{ }

void
MockOutput::createDirectory(const FilePath &path)
{
  if(exists(path))
    throw OutputPluginException("Cannot create directory because specified path already exists");
  FilePath parent_dir = path.parent_path(); 
  if(!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot create directory because parent path of specified path doesn't exists");
    else if(!parent_dir.empty())
      createDirectory(parent_dir);
  }

  file_list.push_back(std::make_pair(path, Directory));
}

void
MockOutput::removeDirectory(const FilePath &path)
{
  if (!exists(path))
    throw OutputPluginException("Cannot remove nonexisting directory");

  FileList::iterator file_iterator = getIterator(path);
  assert(file_iterator != file_list.end());
  file_list.erase(file_iterator);
}

/* ------------------------------------------------------------------------- */

bool
MockOutput::exists(const FilePath &path) const
{
  if (path.empty())
    return false;
  
  FileList::const_iterator file_iterator = getIterator(path);
  return file_iterator != file_list.end();
}

void
MockOutput::move(const FilePath &source_path, const FilePath &destination_path)
{
  if (!exists(source_path))
    throw OutputPluginException("Cannot move because source path doesn't exists");
  if (!overrideTarget() && exists(destination_path))
    throw OutputPluginException("Cannot move because target path exists");

  FilePath parent_dir = destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      createDirectory(parent_dir);
  }

  FileList::iterator file_iterator = getIterator(source_path);
  assert(file_iterator != file_list.end());

  file_iterator->first = destination_path;
}

void
MockOutput::copy(const FilePath &source_path, const FilePath &destination_path)
{
  if (!exists(source_path))
    throw OutputPluginException("Cannot copy because source path doesn't exists");
  if (!overrideTarget() && exists(destination_path))
    throw OutputPluginException("Cannot copy because target path exists");

  FilePath parent_dir = destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      createDirectory(parent_dir);
  }

  FileList::iterator file_iterator = getIterator(source_path);
  assert(file_iterator != file_list.end());

  file_list.push_back(std::make_pair(destination_path, file_iterator->second));
}

void
MockOutput::link(const FilePath &source_path, const FilePath &destination_path)
{
  if (!exists(source_path))
    throw OutputPluginException("Cannot copy because source path doesn't exists");
  if (!overrideTarget() && exists(destination_path))
    throw OutputPluginException("Cannot copy because target path exists");

  FilePath parent_dir = destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      createDirectory(parent_dir);
  }

  FileList::iterator file_iterator = getIterator(source_path);
  assert(file_iterator != file_list.end());

  file_list.push_back(std::make_pair(destination_path, file_iterator->second));
  link_list.push_back(std::make_pair(destination_path, file_iterator->first));
}

FilePath
MockOutput::resolveLink(const FilePath &path) const
{
  if (!exists(path))
    throw OutputPluginException("Cannot resolve link because specified path doesn't exists");

  LinkList::const_iterator link_iterator = getLinkIterator(path); 
  if (link_iterator == link_list.end())
    throw OutputPluginException("Specified file is not a link");
  return link_iterator->second;
}

/* ------------------------------------------------------------------------- */

void
MockOutput::createFile(const FilePath &path)
{
  assert(!exists(path));
  file_list.push_back(std::make_pair(path, File));
}

MockOutput::FileList::iterator
MockOutput::getIterator(const FilePath &path)
{
  FileList::iterator file_iterator = std::find(file_list.begin(), file_list.end(), std::make_pair(path, File));
  if (file_iterator == file_list.end())
    file_iterator = std::find(file_list.begin(), file_list.end(), std::make_pair(path, Directory));
  return file_iterator;
}

MockOutput::FileList::const_iterator
MockOutput::getIterator(const FilePath &path) const
{
  FileList::const_iterator file_iterator = std::find(file_list.begin(), file_list.end(), std::make_pair(path, File));
  if (file_iterator == file_list.end())
    file_iterator = std::find(file_list.begin(), file_list.end(), std::make_pair(path, Directory));
  return file_iterator;
}

MockOutput::LinkList::iterator
MockOutput::getLinkIterator(const FilePath &path)
{
  LinkList::iterator link_iterator = link_list.begin();
  for(; link_iterator != link_list.end(); ++link_iterator) {
    if (link_iterator->first == path)
      return link_iterator;
  }
  return link_iterator;
}

MockOutput::LinkList::const_iterator
MockOutput::getLinkIterator(const FilePath &path) const
{
  LinkList::const_iterator link_iterator = link_list.begin();
  for(; link_iterator != link_list.end(); ++link_iterator) {
    if (link_iterator->first == path)
      return link_iterator;
  }
  return link_iterator;
}

} /* namespace mru */

