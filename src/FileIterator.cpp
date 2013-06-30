#include "FileIterator.hpp"
#include "glue.hpp"
#include "make_relative_fix.hpp"

namespace mru
{

FileIterator::FileIterator(void)
  : m_bfs_iterator(),
    m_include_directories(true), m_include_files(true)
{ }

FileIterator::FileIterator(const self_type &a_other)
  : m_bfs_iterator(a_other.m_bfs_iterator), m_base_path(a_other.m_base_path),
    m_include_directories(true), m_include_files(true)
{ }

//FileIterator::FileIterator(const filepath_type &a_path)
//  : m_bfs_iterator(a_path), m_base_path(a_path)
//{ }

FileIterator::~FileIterator(void)
{ }

FileIterator::FileIterator(const filepath_type &a_path, bool a_directory, bool a_file)
  : m_bfs_iterator(a_path), m_base_path(a_path),
    m_include_directories(a_directory), m_include_files(a_file)
{
  if(!(a_directory + a_file))
    m_bfs_iterator = bfs::recursive_directory_iterator();

  if(!m_include_directories)
    progress_to_next_directory();
  if(!m_include_files)
    progress_to_next_file();
}

/* ------------------------------------------------------------------------- */

const bfs::recursive_directory_iterator &
FileIterator::bfs_iterator(void) const
{
  return m_bfs_iterator;
}

UnicodeString
FileIterator::base_directory(void) const
{
  return glue_cast<UnicodeString>(m_base_path);
}

UnicodeString
FileIterator::base_filename(void) const
{
  return glue_cast<UnicodeString>(m_bfs_iterator->path());
}

UnicodeString
FileIterator::directory(void) const
{
  return glue_cast<UnicodeString>( bfs::make_relative(
          m_base_path,
          m_bfs_iterator->path().parent_path()
         ));
}

UnicodeString
FileIterator::filename(void) const
{
  return glue_cast<UnicodeString>( bfs::make_relative(
          m_base_path,
          m_bfs_iterator->path()
         ));
}

UnicodeString
FileIterator::bare_filename(void) const
{
  return glue_cast<UnicodeString>( 
          m_bfs_iterator->path().filename()
         );
}

FileIterator::self_type &
FileIterator::operator++(void)
{
  ++m_bfs_iterator;
  if(!m_include_directories)
    progress_to_next_directory();
  if(!m_include_files)
    progress_to_next_file();
  return *this;
}

FileIterator::self_type
FileIterator::operator++(int)
{
  self_type tmp(*this);
  ++m_bfs_iterator;
  if(!m_include_directories)
    progress_to_next_directory();
  if(!m_include_files)
    progress_to_next_file();
  return tmp;
}

void
FileIterator::progress_to_next_directory(void)
{
  while(m_bfs_iterator != bfs::recursive_directory_iterator() && bfs::is_directory(m_bfs_iterator->status()))
    ++m_bfs_iterator;
}

void
FileIterator::progress_to_next_file(void)
{
  while(m_bfs_iterator != bfs::recursive_directory_iterator() && bfs::is_regular_file(m_bfs_iterator->status()))
    ++m_bfs_iterator;
}

/* ------------------------------------------------------------------------- */

bool
operator==(const FileIterator::self_type &a_a, const FileIterator::self_type &a_b)
{
  return a_a.m_bfs_iterator == a_b.m_bfs_iterator;
}

bool
operator!=(const FileIterator::self_type &a_a, const FileIterator::self_type &a_b)
{
  return a_a.m_bfs_iterator != a_b.m_bfs_iterator;
}

} /* namespace mru */

