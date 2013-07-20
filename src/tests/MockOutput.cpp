#include "MockOutput.hpp"

namespace mru
{

MockOutput::MockOutput(void)
  : OutputPlugin(static_implementation_name()),
    m_file_list()
{ }

void
MockOutput::createDirectory(const FilePath &a_path)
{
  if(exists(a_path))
    throw OutputPluginException("Cannot create directory because specified path already exists");
  FilePath parent_dir = a_path.parent_path(); 
  if(!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot create directory because parent path of specified path doesn't exists");
    else if(!parent_dir.empty())
      createDirectory(parent_dir);
  }

  m_file_list.push_back(std::make_pair(a_path, Directory));
}

void
MockOutput::removeDirectory(const FilePath &a_path)
{
  if (!exists(a_path))
    throw OutputPluginException("Cannot remove nonexisting directory");

  FileList::iterator file_iterator = getIterator(a_path);
  assert(file_iterator != m_file_list.end());
  m_file_list.erase(file_iterator);
}

/* ------------------------------------------------------------------------- */

bool
MockOutput::exists(const FilePath &a_path) const
{
  if (a_path.empty())
    return false;
  
  FileList::const_iterator file_iterator = getIterator(a_path);
  return file_iterator != m_file_list.end();
}

void
MockOutput::move(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!exists(a_source_path))
    throw OutputPluginException("Cannot move because source path doesn't exists");
  if (!overrideTarget() && exists(a_destination_path))
    throw OutputPluginException("Cannot move because target path exists");

  FilePath parent_dir = a_destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      createDirectory(parent_dir);
  }

  FileList::iterator file_iterator = getIterator(a_source_path);
  assert(file_iterator != m_file_list.end());

  file_iterator->first = a_destination_path;
}

void
MockOutput::copy(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!exists(a_source_path))
    throw OutputPluginException("Cannot copy because source path doesn't exists");
  if (!overrideTarget() && exists(a_destination_path))
    throw OutputPluginException("Cannot copy because target path exists");

  FilePath parent_dir = a_destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      createDirectory(parent_dir);
  }

  FileList::iterator file_iterator = getIterator(a_source_path);
  assert(file_iterator != m_file_list.end());

  m_file_list.push_back(std::make_pair(a_destination_path, file_iterator->second));
}

void
MockOutput::link(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!exists(a_source_path))
    throw OutputPluginException("Cannot copy because source path doesn't exists");
  if (!overrideTarget() && exists(a_destination_path))
    throw OutputPluginException("Cannot copy because target path exists");

  FilePath parent_dir = a_destination_path.parent_path();
  if (!exists(parent_dir)) {
    if (!createNewPath())
      throw OutputPluginException("Cannot move because parent path of specified path doesn't exists");
    else
      createDirectory(parent_dir);
  }

  FileList::iterator file_iterator = getIterator(a_source_path);
  assert(file_iterator != m_file_list.end());

  m_file_list.push_back(std::make_pair(a_destination_path, file_iterator->second));
  m_link_list.push_back(std::make_pair(a_destination_path, file_iterator->first));
}

FilePath
MockOutput::resolveLink(const FilePath &a_path) const
{
  if (!exists(a_path))
    throw OutputPluginException("Cannot resolve link because specified path doesn't exists");

  LinkList::const_iterator link_iterator = getLinkIterator(a_path); 
  if (link_iterator == m_link_list.end())
    throw OutputPluginException("Specified file is not a link");
  return link_iterator->second;
}

/* ------------------------------------------------------------------------- */

void
MockOutput::createFile(const FilePath &a_path)
{
  assert(!exists(a_path));
  m_file_list.push_back(std::make_pair(a_path, File));
}

MockOutput::FileList::iterator
MockOutput::getIterator(const FilePath &a_path)
{
  FileList::iterator file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, File));
  if (file_iterator == m_file_list.end())
    file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, Directory));
  return file_iterator;
}

MockOutput::FileList::const_iterator
MockOutput::getIterator(const FilePath &a_path) const
{
  FileList::const_iterator file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, File));
  if (file_iterator == m_file_list.end())
    file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, Directory));
  return file_iterator;
}

MockOutput::LinkList::iterator
MockOutput::getLinkIterator(const FilePath &a_path)
{
  LinkList::iterator link_iterator = m_link_list.begin();
  for(; link_iterator != m_link_list.end(); ++link_iterator) {
    if (link_iterator->first == a_path)
      return link_iterator;
  }
  return link_iterator;
}

MockOutput::LinkList::const_iterator
MockOutput::getLinkIterator(const FilePath &a_path) const
{
  LinkList::const_iterator link_iterator = m_link_list.begin();
  for(; link_iterator != m_link_list.end(); ++link_iterator) {
    if (link_iterator->first == a_path)
      return link_iterator;
  }
  return link_iterator;
}

} /* namespace mru */

