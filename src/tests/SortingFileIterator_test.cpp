#include "SortingFileIterator_test.hpp"
#include <cppunit/ui/text/TestRunner.h>

#define SORT_COMPARATOR(Name, BODY) \
  namespace { \
  class Name : public SortingFileIterator::SortComparator { \
  public: \
    int operator()(const FilePath &a_path_a, const FilePath &a_path_b) \
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

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(SortingIterator_test::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

