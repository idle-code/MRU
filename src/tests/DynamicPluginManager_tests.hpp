#ifndef DYNAMIC_PLUGIN_MANAGER_TESTS_HPP
#define DYNAMIC_PLUGIN_MANAGER_TESTS_HPP

#include "DynamicPluginManager.hpp"
#include "TestModule.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace mru;
using namespace CppUnit;

class DynamicPluginManager_tests : public TestCase {
public:
  typedef DynamicPluginManager<ITestPlugin> DynamicTestPluginManager;
  DynamicTestPluginManager::Pointer manager;
  void setUp(void);

  void load_nonexisting(void);
  void load_existing(void);
  void load_loaded(void);

  CPPUNIT_TEST_SUITE(DynamicPluginManager_tests);
    CPPUNIT_TEST_EXCEPTION(load_nonexisting, DllModule::Exception);
    CPPUNIT_TEST(load_existing);
    CPPUNIT_TEST(load_loaded);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* DYNAMIC_PLUGIN_MANAGER_TESTS_HPP */

