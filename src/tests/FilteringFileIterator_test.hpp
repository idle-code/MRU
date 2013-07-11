#ifndef FILTERING_FILE_ITERATOR_TEST_HPP
#define FILTERING_FILE_ITERATOR_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "FilteringFileIterator.hpp"
#include "MockFileIterator.hpp"

using namespace CppUnit;
using namespace mru;

class FilteringIterator_test : public TestCase {
public:
  FilteringIterator_test(void);
  std::list<FilePath> files;
  static const FilePath prefix;
  FileIterator::Pointer getIterator(void);

  void true_predicate(void);
  void false_predicate(void);
  void filename_start_predicate(void);
  void extension_predicate(void);

  CPPUNIT_TEST_SUITE(FilteringIterator_test);
    CPPUNIT_TEST(true_predicate);
    CPPUNIT_TEST(false_predicate);
    CPPUNIT_TEST(filename_start_predicate);
    CPPUNIT_TEST(extension_predicate);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* FILTERING_FILE_ITERATOR_TEST_HPP */

