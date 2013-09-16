#include "DynamicPluginManager_tests.hpp"

void
DynamicPluginManager_tests::setUp(void)
{
  manager = boost::make_shared<DynamicTestPluginManager>();
}

/* ------------------------------------------------------------------------- */

void
DynamicPluginManager_tests::load_nonexisting(void)
{
  DllModule::Pointer loaded_module = manager->loadModule("./nonexisting");
}

void
DynamicPluginManager_tests::load_existing(void)
{
  DllModule::Pointer loaded_module = manager->loadModule("./libTestModule.so");
  CPPUNIT_ASSERT(loaded_module);

  DynamicTestPluginManager::FactoryList factory_list = manager->getFactoryList();
  CPPUNIT_ASSERT_EQUAL(2u, factory_list.size());
}

void
DynamicPluginManager_tests::load_loaded(void)
{
  DllModule::Pointer loaded_module1 = manager->loadModule("./libTestModule.so");
  DllModule::Pointer loaded_module2 = manager->loadModule("./libTestModule.so");
  CPPUNIT_ASSERT(loaded_module1);
  CPPUNIT_ASSERT(loaded_module2);

  CPPUNIT_ASSERT(loaded_module1 == loaded_module2);

  DynamicTestPluginManager::FactoryList factory_list = manager->getFactoryList();
  CPPUNIT_ASSERT_EQUAL(2u, factory_list.size());
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(DynamicPluginManager_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

