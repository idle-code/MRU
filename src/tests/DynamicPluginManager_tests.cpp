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
  manager->registerModule("./libTestModule.so");
  DynamicTestPluginManager::FactoryList factory_list = manager->getFactoryList();
  
  CPPUNIT_ASSERT_EQUAL(1, factory_list.size());
}

void
DynamicPluginManager_tests::load_existing(void)
{

}

void
DynamicPluginManager_tests::load_loaded(void)
{

}

void
DynamicPluginManager_tests::create_noon(void)
{

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

