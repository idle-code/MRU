#ifndef METATAG_EXPRESSION_TEST_HPP
#define METATAG_EXPRESSION_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpression.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpression_tests : public TestCase {
public:
  void construction(void);

  CPPUNIT_TEST_SUITE(MetatagExpression_tests);
    CPPUNIT_TEST(construction);
  CPPUNIT_TEST_SUITE_END();
};


#endif /* METATAG_EXPRESSION_TEST_HPP */

