#ifndef GLUE_TEST_HPP
#define GLUE_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "glue.hpp"

using namespace CppUnit;
using namespace mru;

class glue_tests : public TestCase {
public:
  void wxString_and_filepath(void);
  void UnicodeString_and_filepath(void);
  void UnicodeString_and_wstring(void);

  CPPUNIT_TEST_SUITE(glue_tests);
    CPPUNIT_TEST(wxString_and_filepath);
    CPPUNIT_TEST(UnicodeString_and_filepath);
    CPPUNIT_TEST(UnicodeString_and_wstring);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* GLUE_TEST_HPP */

