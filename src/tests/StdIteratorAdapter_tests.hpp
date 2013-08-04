#ifndef STD_ITERATOR_ADAPTER_TESTS_HPP
#define STD_ITERATOR_ADAPTER_TESTS_HPP

#include "StdIteratorAdapter.hpp"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <list>

using namespace CppUnit;
using namespace mru;

class StdIteratorAdapter_tests : public TestCase {
public:
  typedef std::string ValueType;
  typedef std::list<ValueType> ContainerType;
  typedef StdIteratorAdapter<ContainerType::iterator> Iterator;
  typedef ConstStdIteratorAdapter<ContainerType::const_iterator> ConstIterator;
public:
  ValueType val1, val2, val3;
  ContainerType container;
  const ContainerType &const_container;

  StdIteratorAdapter_tests(void);
  void SetUp(void); 
  void TearDown(void); 

  void iterator_end(void);
  void iterator_progress(void);
  void iterator_reset(void);

  void const_iterator_end(void);
  void const_iterator_progress(void);
  void const_iterator_reset(void);

  CPPUNIT_TEST_SUITE(StdIteratorAdapter_tests);
    CPPUNIT_TEST(iterator_end);
    CPPUNIT_TEST(iterator_progress);
    CPPUNIT_TEST(iterator_reset);

    CPPUNIT_TEST(const_iterator_end);
    CPPUNIT_TEST(const_iterator_progress);
    CPPUNIT_TEST(const_iterator_reset);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* STD_ITERATOR_ADAPTER_TESTS_HPP */

