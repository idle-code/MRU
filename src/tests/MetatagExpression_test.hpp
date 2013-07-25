#ifndef METATAG_EXPRESSION_TEST_HPP
#define METATAG_EXPRESSION_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpression.hpp"
#include "types.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpression_tests : public TestCase {
public:
  UnicodeString expr_str;
public:
  void initial_state(void);
  void empty_expr(void);
  void static_expr(void);

  CPPUNIT_TEST_SUITE(MetatagExpression_tests);
    CPPUNIT_TEST(initial_state);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
  CPPUNIT_TEST_SUITE_END();
};


#endif /* METATAG_EXPRESSION_TEST_HPP */

