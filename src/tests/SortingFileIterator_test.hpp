#ifndef SORTING_FILE_ITERATOR_TEST_HPP
#define SORTING_FILE_ITERATOR_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "SortingFileIterator.hpp"
#include "MockFileIterator.hpp"

using namespace CppUnit;
using namespace mru;

class SortingIterator_test : public TestCase {
public:
  SortingIterator_test(void);
  std::list<FilePath> files;
  static const FilePath prefix;
  FileIterator::Pointer getIterator(void);

  void no_sort(void);

  CPPUNIT_TEST_SUITE(SortingIterator_test);
    CPPUNIT_TEST(no_sort);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* SORTING_FILE_ITERATOR_TEST_HPP */

