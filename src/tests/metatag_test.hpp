#ifndef METATAG_TEST_HPP
#define METATAG_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "metatag/expression.hpp"

using namespace CppUnit;
using namespace mru;

class metatag_tests : public TestCase {
public:
  void construction(void);
  //void 

  CPPUNIT_TEST_SUITE(metatag_tests);
    CPPUNIT_TEST(construction);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* METATAG_TEST_HPP */

