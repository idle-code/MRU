#include "SortingFileIterator_tests.hpp"
#include <cppunit/ui/text/TestRunner.h>

#define SORT_COMPARATOR(Name, BODY) \
  namespace { \
  class Name : public SortingFileIterator::SortComparator { \
  public: \
    int operator()(const FilePath &path_a, const FilePath &path_b) \
    { \
      BODY \
    } \
  }; \
  }

const FilePath
SortingIterator_test::prefix = "/some/dummy/dir";

SortingIterator_test::SortingIterator_test(void)
{
  files.push_back(prefix / "b");
  files.push_back(prefix / "A2");
  files.push_back(prefix / "a");
  files.push_back(prefix / "A1");
  files.push_back(prefix / "dir" / "application.log");
  files.push_back(prefix / "spam" / "licence.txt");
  files.push_back(prefix / "dir" / "system.log");
  files.push_back(prefix / "spam" / "mails.txt");
  files.push_back(prefix / "spam" / "readme.txt");
  files.push_back(prefix / "dir" / "B.log");
  files.push_back(prefix / "c");
  files.push_back(prefix / "GRAIL" / "and_deeper" / "hole1");
  files.push_back(prefix / "GRAIL" / "somewhat shallow" / "OtherHole");
  files.push_back(prefix / "GRAIL" / "abandon.log");
}

FileIterator::Pointer
SortingIterator_test::getIterator(void)
{
  FileIterator::Pointer file_iterator = FileIterator::Pointer(new MockFileIterator(files));
  CPPUNIT_ASSERT(!file_iterator->atEnd());
  return file_iterator;
}

/* ------------------------------------------------------------------------- */

SORT_COMPARATOR(DummyComparer,
  return 0;
)

void
SortingIterator_test::no_sort(void)
{
  FileIterator::Pointer iter = SortingFileIterator::wrap(getIterator(), new DummyComparer());

  CPPUNIT_ASSERT(!iter->atEnd());
  std::list<FilePath>::iterator i = files.begin();
  for(; !iter->atEnd() && i != files.end(); iter->next(), ++i) {
    CPPUNIT_ASSERT(i != files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
  }
  CPPUNIT_ASSERT(i == files.end());
  CPPUNIT_ASSERT(iter->atEnd());

  iter->first();
  CPPUNIT_ASSERT(!iter->atEnd());

  i = files.begin();
  do {
    CPPUNIT_ASSERT(i != files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
    ++i;
  } while(iter->next() && i != files.end());
  CPPUNIT_ASSERT(i == files.end());
  CPPUNIT_ASSERT(iter->atEnd());
}

/* ------------------------------------------------------------------------- */

SORT_COMPARATOR(DescendingComparer,
  return path_a < path_b;
)

void
SortingIterator_test::descending_sort(void)
{
  std::list<FilePath> sorted_files;
  sorted_files.push_back(prefix / "A1");
  sorted_files.push_back(prefix / "A2");
  sorted_files.push_back(prefix / "GRAIL" / "abandon.log");
  sorted_files.push_back(prefix / "GRAIL" / "and_deeper" / "hole1");
  sorted_files.push_back(prefix / "GRAIL" / "somewhat shallow" / "OtherHole");
  sorted_files.push_back(prefix / "a");
  sorted_files.push_back(prefix / "b");
  sorted_files.push_back(prefix / "c");
  sorted_files.push_back(prefix / "dir" / "B.log");
  sorted_files.push_back(prefix / "dir" / "application.log");
  sorted_files.push_back(prefix / "dir" / "system.log");
  sorted_files.push_back(prefix / "spam" / "licence.txt");
  sorted_files.push_back(prefix / "spam" / "mails.txt");
  sorted_files.push_back(prefix / "spam" / "readme.txt");

  FileIterator::Pointer iter = SortingFileIterator::wrap(getIterator(), new DescendingComparer());

  CPPUNIT_ASSERT(!iter->atEnd());
  std::list<FilePath>::iterator i = sorted_files.begin();
  for(; !iter->atEnd() && i != sorted_files.end(); iter->next(), ++i) {
    CPPUNIT_ASSERT(i != sorted_files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
  }
  CPPUNIT_ASSERT(i == sorted_files.end());
  CPPUNIT_ASSERT(iter->atEnd());

  iter->first();
  CPPUNIT_ASSERT(!iter->atEnd());

  i = sorted_files.begin();
  do {
    CPPUNIT_ASSERT(i != sorted_files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
    ++i;
  } while(iter->next() && i != sorted_files.end());
  CPPUNIT_ASSERT(i == sorted_files.end());
  CPPUNIT_ASSERT(iter->atEnd());
}

/* ------------------------------------------------------------------------- */

SORT_COMPARATOR(AscendingComparer,
  return path_a.string() > path_b.string();
)

void
SortingIterator_test::ascending_sort(void)
{
  std::list<FilePath> sorted_files;
  sorted_files.push_back(prefix / "spam" / "readme.txt");
  sorted_files.push_back(prefix / "spam" / "mails.txt");
  sorted_files.push_back(prefix / "spam" / "licence.txt");
  sorted_files.push_back(prefix / "dir" / "system.log");
  sorted_files.push_back(prefix / "dir" / "application.log");
  sorted_files.push_back(prefix / "dir" / "B.log");
  sorted_files.push_back(prefix / "c");
  sorted_files.push_back(prefix / "b");
  sorted_files.push_back(prefix / "a");
  sorted_files.push_back(prefix / "GRAIL" / "somewhat shallow" / "OtherHole");
  sorted_files.push_back(prefix / "GRAIL" / "and_deeper" / "hole1");
  sorted_files.push_back(prefix / "GRAIL" / "abandon.log");
  sorted_files.push_back(prefix / "A2");
  sorted_files.push_back(prefix / "A1");

  FileIterator::Pointer iter = SortingFileIterator::wrap(getIterator(), new AscendingComparer());

  CPPUNIT_ASSERT(!iter->atEnd());
  std::list<FilePath>::iterator i = sorted_files.begin();
  for(; !iter->atEnd() && i != sorted_files.end(); iter->next(), ++i) {
    CPPUNIT_ASSERT(i != sorted_files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
  }
  CPPUNIT_ASSERT(i == sorted_files.end());
  CPPUNIT_ASSERT(iter->atEnd());

  iter->first();
  CPPUNIT_ASSERT(!iter->atEnd());

  i = sorted_files.begin();
  do {
    CPPUNIT_ASSERT(i != sorted_files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
    ++i;
  } while(iter->next() && i != sorted_files.end());
  CPPUNIT_ASSERT(i == sorted_files.end());
  CPPUNIT_ASSERT(iter->atEnd());
}

/* ------------------------------------------------------------------------- */

SORT_COMPARATOR(LengthComparer,
  int a_len = path_a.string().length(); 
  int b_len = path_b.string().length(); 
  if(a_len < b_len)
    return true;
  else if(a_len > b_len)
    return false;
  else // a_len == b_len
    return path_a.string() < path_b.string();
)

void
SortingIterator_test::length_sort(void)
{
  std::list<FilePath> sorted_files;
  sorted_files.push_back(prefix / "a");
  sorted_files.push_back(prefix / "b");
  sorted_files.push_back(prefix / "c");
  sorted_files.push_back(prefix / "A1");
  sorted_files.push_back(prefix / "A2");
  sorted_files.push_back(prefix / "dir" / "B.log");
  sorted_files.push_back(prefix / "dir" / "system.log");
  sorted_files.push_back(prefix / "spam" / "mails.txt");
  sorted_files.push_back(prefix / "spam" / "readme.txt");
  sorted_files.push_back(prefix / "spam" / "licence.txt");
  sorted_files.push_back(prefix / "GRAIL" / "abandon.log");
  sorted_files.push_back(prefix / "dir" / "application.log");
  sorted_files.push_back(prefix / "GRAIL" / "and_deeper" / "hole1");
  sorted_files.push_back(prefix / "GRAIL" / "somewhat shallow" / "OtherHole");

  FileIterator::Pointer iter = SortingFileIterator::wrap(getIterator(), new LengthComparer());

  CPPUNIT_ASSERT(!iter->atEnd());
  std::list<FilePath>::iterator i = sorted_files.begin();
  for(; !iter->atEnd() && i != sorted_files.end(); iter->next(), ++i) {
    CPPUNIT_ASSERT(i != sorted_files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
  }
  CPPUNIT_ASSERT(i == sorted_files.end());
  CPPUNIT_ASSERT(iter->atEnd());

  iter->first();
  CPPUNIT_ASSERT(!iter->atEnd());

  i = sorted_files.begin();
  do {
    CPPUNIT_ASSERT(i != sorted_files.end());
    CPPUNIT_ASSERT_EQUAL(*i, iter->getFilePath());
    ++i;
  } while(iter->next() && i != sorted_files.end());
  CPPUNIT_ASSERT(i == sorted_files.end());
  CPPUNIT_ASSERT(iter->atEnd());

}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(SortingIterator_test::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

