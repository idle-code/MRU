#ifndef DLL_MODULE_TESTS_HPP
#define DLL_MODULE_TESTS_HPP

#include "DllModule.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace mru;
using namespace CppUnit;

class DllModule_tests : public TestCase {
public:
  DllModule::Pointer module;
  void setUp(void);

  void load_nonexisting(void);
  void load_existing_non_dll(void);
  void load_existing(void);
  void unload(void);
  void unload_not_loaded(void);
  void load_nonexisting_symbol(void);
  void load_symbol(void);

  CPPUNIT_TEST_SUITE(DllModule_tests);
    CPPUNIT_TEST_EXCEPTION(load_nonexisting, DllModule::Exception);
    CPPUNIT_TEST_EXCEPTION(load_existing_non_dll, DllModule::Exception);
    CPPUNIT_TEST(load_existing);
    CPPUNIT_TEST(unload);
    CPPUNIT_TEST(unload_not_loaded);
    CPPUNIT_TEST(load_nonexisting_symbol);
    CPPUNIT_TEST(load_symbol);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* DLL_MODULE_TESTS_HPP */

