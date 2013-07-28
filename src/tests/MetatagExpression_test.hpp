#ifndef METATAG_EXPRESSION_TEST_HPP
#define METATAG_EXPRESSION_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "MetatagExpression.hpp"
#include "types.hpp"

using namespace CppUnit;
using namespace mru;

class MetatagExpression_tests : public TestCase {
private:
  UnicodeString expr_str;
public:
  void setUp(void);

  void initial_state(void);
  void empty_expr(void);
  void static_expr(void);
  void flat_expr(void);
  void nested_expr(void);
  void invalid_expr(void);
  void escaped_expr(void);
  void double_escaped_expr(void);
  void escaped_normal_expr(void);

  void static_expr_evaluation(void);


#if 1
  CPPUNIT_TEST_SUITE(MetatagExpression_tests);
    CPPUNIT_TEST(initial_state);
    CPPUNIT_TEST(empty_expr);
    CPPUNIT_TEST(static_expr);
    CPPUNIT_TEST(flat_expr);
    CPPUNIT_TEST(nested_expr);
    CPPUNIT_TEST(invalid_expr);
    CPPUNIT_TEST(escaped_expr);
    CPPUNIT_TEST(double_escaped_expr);
    CPPUNIT_TEST(escaped_normal_expr);
    //CPPUNIT_TEST(static_expr_evaluation);
    //CPPUNIT_TEST(flat_expr);
  CPPUNIT_TEST_SUITE_END();
#else
  CPPUNIT_TEST_SUITE(MetatagExpression_tests);
  CPPUNIT_TEST_SUITE_END();
#endif
};

#endif /* METATAG_EXPRESSION_TEST_HPP */

