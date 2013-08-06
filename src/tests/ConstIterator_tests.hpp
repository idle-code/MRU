#ifndef CONST_ITERATOR_TESTS_HPP
#define CONST_ITERATOR_TESTS_HPP

#include "Iterator.hpp"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <list>

using namespace CppUnit;
using namespace mru;

template<typename ValueType>
class ConstIterator_tests : public TestCase {
public:
  typedef ConstIterator<ValueType> ConstIterator;
  typedef std::list<ValueType> ValueList;
public:
  virtual ValueList getSampleValues(void) = 0;
  virtual typename ConstIterator::Pointer getConstIterator(const ValueList &values_in_container) = 0;
  
  void end(void);
  void progress(void);
  void reset(void);

  CPPUNIT_TEST_SUITE(ConstIterator_tests);
    CPPUNIT_TEST(end);
    CPPUNIT_TEST(progress);
    CPPUNIT_TEST(reset);
  CPPUNIT_TEST_SUITE_END();
protected:
  typename ConstIterator::Pointer iterator_ptr;
};

#define CONST_ITERATOR_TESTS_IMPL_HPP
#include "ConstIterator_tests_impl.hpp"
#undef CONST_ITERATOR_TESTS_IMPL_HPP

#endif /* CONST_ITERATOR_TESTS_HPP */

