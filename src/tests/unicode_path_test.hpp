#ifndef TEXT_PATH_TEST_HPP_HEADER 
#define TEXT_PATH_TEST_HPP_HEADER

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../unicode_variant_tree.hpp"

using namespace CppUnit;
using namespace mru;

namespace CppUnit {
template<>
struct assertion_traits<std::wstring>
{
  static bool equal(const std::wstring &a_a, const std::wstring &a_b)
  {
    return a_a == a_b;
  }

  static std::string toString(const std::wstring &a_value)
  {
    return std::string(a_value.begin(), a_value.end());
  }
};
} /* namespace CppUnit */

class unicode_path_tests : public TestCase {
private:
public:
  unicode_path_tests();
  ~unicode_path_tests();
  
  typedef mru::unicode_path::value_type value_type;
  
  void construction_and_assignment(void);
  void base_constructor__separator_in_element__exception(void);
  void separator_change__separator_in_element__exception(void);
  
  void concatenation(void);
  void direct_path_concatenation__exception(void);
  void direct_path_concatenation_custom_separator__exception(void);
  
  CPPUNIT_TEST_SUITE(unicode_path_tests);
    CPPUNIT_TEST(construction_and_assignment);
    CPPUNIT_TEST_EXCEPTION(base_constructor__separator_in_element__exception, unicode_path::invalid_element_exception);
    CPPUNIT_TEST(concatenation);
    CPPUNIT_TEST_EXCEPTION(direct_path_concatenation__exception, unicode_path::invalid_argument_exception);
    CPPUNIT_TEST_EXCEPTION(direct_path_concatenation_custom_separator__exception, unicode_path::invalid_argument_exception);
    CPPUNIT_TEST_EXCEPTION(separator_change__separator_in_element__exception, unicode_path::invalid_element_exception);
  CPPUNIT_TEST_SUITE_END();
  
}; 

#endif /* TEXT_PATH_TEST_HPP_HEADER */
