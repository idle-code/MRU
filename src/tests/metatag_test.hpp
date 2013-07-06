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
  void tokenizing(void);
  void empty_expression(void);
  void unclosed_area_of_effect(void);
  void unclosed_arguments(void);
  void no_arguments(void);
  void space_metatag(void);
  void no_metatag_name(void);
  void arg_start_in_text(void);
  void arg_end_in_text(void);
  void aoe_start_in_text(void);
  void aoe_end_in_text(void);

  CPPUNIT_TEST_SUITE(metatag_tests);
    CPPUNIT_TEST(construction);
    //CPPUNIT_TEST(tokenizing);
    //CPPUNIT_TEST(empty_expression);
    //CPPUNIT_TEST_EXCEPTION(unclosed_area_of_effect, MetatagExpressionException);
    //CPPUNIT_TEST_EXCEPTION(unclosed_arguments, MetatagExpressionException);
    //CPPUNIT_TEST_EXCEPTION(no_arguments, MetatagExpressionException);
    //CPPUNIT_TEST_EXCEPTION(space_metatag, MetatagExpressionException);
    //CPPUNIT_TEST_EXCEPTION(no_metatag_name, MetatagExpressionException);
    //CPPUNIT_TEST(arg_start_in_text);
    //CPPUNIT_TEST(arg_end_in_text);
    //CPPUNIT_TEST(aoe_start_in_text);
    //CPPUNIT_TEST_EXCEPTION(aoe_end_in_text, MetatagExpressionException);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* METATAG_TEST_HPP */

