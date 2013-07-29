#include "FilteringFileIterator_tests.hpp"
#include <cppunit/ui/text/TestRunner.h>

#define FILTER_PREDICATE(Name, BODY) \
  namespace { \
  class Name : public FilteringFileIterator::FilterPredicate { \
  public: \
    bool operator()(const FilePath &path) \
    { \
      BODY \
    } \
  }; \
  }

const FilePath
FilteringIterator_test::prefix = "/some/dummy/dir";

FilteringIterator_test::FilteringIterator_test(void)
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
FilteringIterator_test::getIterator(void)
{
  FileIterator::Pointer file_iterator = FileIterator::Pointer(new MockFileIterator(files));
  CPPUNIT_ASSERT(!file_iterator->atEnd());
  return file_iterator;
}

/* ------------------------------------------------------------------------- */

FILTER_PREDICATE(TruePredicate,
  return true;
)

void
FilteringIterator_test::true_predicate(void)
{
  FileIterator::Pointer iter = FilteringFileIterator::wrap(getIterator(), new TruePredicate());

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

FILTER_PREDICATE(FalsePredicate,
  return false;
)

void
FilteringIterator_test::false_predicate(void)
{
  FileIterator::Pointer iter = FilteringFileIterator::wrap(getIterator(), new FalsePredicate());
  CPPUNIT_ASSERT(iter->atEnd());
  iter->first();
  CPPUNIT_ASSERT(iter->atEnd());
}

/* ------------------------------------------------------------------------- */

FILTER_PREDICATE(FilenameStartPredicate,
  return path.filename().string().find("a") == 0; //if filename starts with 'a'
)

void
FilteringIterator_test::filename_start_predicate(void)
{
  FileIterator::Pointer iter = FilteringFileIterator::wrap(getIterator(), new FilenameStartPredicate());

  std::list<FilePath> files;
  files.push_back(prefix / "a");
  files.push_back(prefix / "dir" / "application.log");
  files.push_back(prefix / "GRAIL" / "abandon.log");

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

FILTER_PREDICATE(ExtensionPredicate,
  return path.extension().string() == ".log";
)

void
FilteringIterator_test::extension_predicate(void)
{
  FileIterator::Pointer iter = FilteringFileIterator::wrap(getIterator(), new ExtensionPredicate());

  std::list<FilePath> files;
  files.push_back(prefix / "dir" / "application.log");
  files.push_back(prefix / "dir" / "system.log");
  files.push_back(prefix / "dir" / "B.log");
  files.push_back(prefix / "GRAIL" / "abandon.log");

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
  runner.addTest(FilteringIterator_test::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */


