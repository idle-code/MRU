#ifndef MRU_CORE_TESTS_HPP
#define MRU_CORE_TESTS_HPP

#include "MruCore.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace mru;
using namespace CppUnit;

class MruCore_tests : public TestCase {
public:
  void without_start(void);
  void without_arguments(void);

  CPPUNIT_TEST_SUITE(MruCore_tests);
    CPPUNIT_TEST(without_start);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* MRU_CORE_TESTS_HPP */

