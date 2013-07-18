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
    throw OutputPluginException("Cannon create directory because specified path already exists");
  m_file_list.push_back(std::make_pair(a_path, Directory));
}

void
MockOutput::removeDirectory(const FilePath &a_path)
{
  if (fileExists(a_path))
    throw OutputPluginException("Cannot remove directory because specified path targets file");
  if (!directoryExists(a_path))
    throw OutputPluginException("Cannot remove nonexisting directory");
  FileList::iterator file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, Directory));
  assert(file_iterator != m_file_list.end());
  m_file_list.erase(file_iterator);
}

void
MockOutput::createFile(const FilePath &a_path)
{
  assert(!exists(a_path));
  m_file_list.push_back(std::make_pair(a_path, File));
}

/* ------------------------------------------------------------------------- */

void
MockOutput::moveFile(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!fileExists(a_source_path))
    throw OutputPluginException("Specified source path doesn't exists");
  move(a_source_path, a_destination_path);
}

void
MockOutput::moveDirectory(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!directoryExists(a_source_path))
    throw OutputPluginException("Specified source path doesn't exists");
  move(a_source_path, a_destination_path);
}

void
MockOutput::move(const FilePath &a_source_path, const FilePath &a_destination_path)
{
  if (!overwriteTarget() && exists(a_destination_path))
    throw OutputPluginException("Cannot move because target path exists");

  FileList::iterator file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_source_path, File));
  if (file_iterator == m_file_list.end())
    file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_source_path, Directory));
  assert(file_iterator != m_file_list.end());

  file_iterator->first = a_destination_path;
}

/* ------------------------------------------------------------------------- */

bool
MockOutput::fileExists(const FilePath &a_path) const
{
  FileList::const_iterator file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, File));
  return file_iterator != m_file_list.end();
}

bool
MockOutput::directoryExists(const FilePath &a_path) const
{
  FileList::const_iterator file_iterator = std::find(m_file_list.begin(), m_file_list.end(), std::make_pair(a_path, Directory));
  return file_iterator != m_file_list.end();
}

} /* namespace mru */

