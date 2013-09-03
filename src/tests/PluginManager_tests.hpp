#ifndef PLUGIN_MANAGER_TESTS_HPP
#define PLUGIN_MANAGER_TESTS_HPP

#include "PluginManager.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace mru;
using namespace CppUnit;

class ITestPlugin {
public:
  typedef boost::shared_ptr<ITestPlugin> Pointer;

  virtual std::string sayHello(void) = 0;
};

class PluginManager_tests : public TestCase {
public:
  typedef PluginManager<ITestPlugin> TestPluginManager;
  TestPluginManager::Pointer manager;
  void setUp(void);

  void null_factory(void);
  void create_morning(void);
  void create_evening(void);
  void create_nonexisting(void);
  void register_duplicate(void);
  void factory_list(void);

  CPPUNIT_TEST_SUITE(PluginManager_tests);
    CPPUNIT_TEST_EXCEPTION(null_factory, TestPluginManager::Exception);
    CPPUNIT_TEST(create_morning);
    CPPUNIT_TEST(create_evening);
    CPPUNIT_TEST_EXCEPTION(create_nonexisting, TestPluginManager::Exception);
    CPPUNIT_TEST_EXCEPTION(register_duplicate, TestPluginManager::Exception);
    CPPUNIT_TEST(factory_list);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* PLUGIN_MANAGER_TESTS_HPP */

