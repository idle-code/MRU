#include "FileIterator.hpp"
#include "glue.hpp"
#include "make_relative_fix.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

FileIterator::FileIterator(void)
  : m_bfs_iterator(),
    m_include_directories(true), m_include_files(true)
{ }

FileIterator::FileIterator(const self_type &a_other)
  : m_bfs_iterator(a_other.m_bfs_iterator), m_base_path(a_other.m_base_path),
    m_include_directories(true), m_include_files(true), m_filter()
{ }

//FileIterator::FileIterator(const filepath_type &a_path)
//  : m_bfs_iterator(a_path), m_base_path(a_path)
//{ }

FileIterator::~FileIterator(void)
{ } 

FileIterator::FileIterator(const filepath_type &a_path, bool a_directory, bool a_file, const UnicodeString &a_filter)
  : m_bfs_iterator(a_path), m_base_path(a_path),
    m_include_directories(a_directory), m_include_files(a_file), m_filter(a_filter)
{
  //m_filter.findAndReplace(glue_cast<UnicodeString>("*"), glue_cast<UnicodeString>(".*"));
  //m_filter.findAndReplace(glue_cast<UnicodeString>("?"), glue_cast<UnicodeString>(".?"));
  if(!(a_directory + a_file))
    m_bfs_iterator = bfs::recursive_directory_iterator();
  progress_if_needed();
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
FileIterator::absolute_filename(void) const
{
  return glue_cast<UnicodeString>(m_bfs_iterator->path());
}

UnicodeString
FileIterator::absolute_directory(void) const
{
  return glue_cast<UnicodeString>(m_bfs_iterator->path().parent_path());
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
  progress_if_needed();
  return *this;
}

FileIterator::self_type
FileIterator::operator++(int)
{
  self_type tmp(*this);
  ++m_bfs_iterator;
  progress_if_needed();
  return tmp;
}

void
FileIterator::progress_if_needed(void)
{
  bfs::recursive_directory_iterator end_iterator;

  if(m_filter.length() > 0) {
    UErrorCode status = U_ZERO_ERROR;
    //VAL(glue_cast<std::string>(m_filter));
    icu::RegexMatcher matcher(m_filter, 0, status);
    //VAL(u_errorName(status));
    if(!U_FAILURE(status)) {
      while(m_bfs_iterator != end_iterator) {
        matcher.reset(bare_filename());
        if(matcher.matches(status)) {
          break;
        }

        if(U_FAILURE(status)) {
          ERR("RegexMatcher error");
          break;
        } 
        ++m_bfs_iterator;
      }
    } else {
      ERR("RegexMatcher setup failed");
    }
  }

  if(!m_include_directories) {
    while(m_bfs_iterator != end_iterator &&
          bfs::is_directory(m_bfs_iterator->status()))
      ++m_bfs_iterator;
  }

  if(!m_include_files) {
    while(m_bfs_iterator != end_iterator &&
          bfs::is_regular_file(m_bfs_iterator->status()))
      ++m_bfs_iterator;
  }
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

