#include "PluginManager_tests.hpp"

/* ------------------------------------------------------------------------- */

void
PluginManager_tests::setUp(void)
{
  manager = boost::make_shared<TestPluginManager>();
  manager->registerFactory(MorningTestPlugin::Factory::createFactory("Morning"));
  manager->registerFactory(EveningTestPlugin::Factory::createFactory("Evening"));
}

/* ------------------------------------------------------------------------- */

void
PluginManager_tests::null_factory(void)
{
  manager->registerFactory(PluginFactory<MorningTestPlugin, ITestPlugin>::Pointer()); //throw
}

void
PluginManager_tests::create_morning(void)
{
  ITestPlugin::Pointer morning = manager->createPlugin("Morning");
  CPPUNIT_ASSERT(morning);
  CPPUNIT_ASSERT_EQUAL(std::string("Morning!"), morning->sayHello());

  ITestPlugin::Pointer morning2 = manager->createPlugin("Morning");
  CPPUNIT_ASSERT(morning2);
  CPPUNIT_ASSERT_EQUAL(std::string("Morning!"), morning2->sayHello());
}

void
PluginManager_tests::create_evening(void)
{
  ITestPlugin::Pointer evening = manager->createPlugin("Evening");
  CPPUNIT_ASSERT(evening);
  CPPUNIT_ASSERT_EQUAL(std::string("Good evening!"), evening->sayHello());

  ITestPlugin::Pointer evening2 = manager->createPlugin("Evening");
  CPPUNIT_ASSERT(evening2);
  CPPUNIT_ASSERT_EQUAL(std::string("Good evening!"), evening2->sayHello());
}

void
PluginManager_tests::create_nonexisting(void)
{
  manager->createPlugin("Afternoon"); //throw
}

void
PluginManager_tests::register_duplicate(void)
{
  manager->registerFactory(PluginFactory<EveningTestPlugin, ITestPlugin>::createFactory("Morning")); //throw
}

void
PluginManager_tests::factory_list(void)
{
  std::list<TestPluginManager::AbstractPluginFactory::Pointer> factory_list = manager->getFactoryList();
  CPPUNIT_ASSERT(2u == factory_list.size());
  TestPluginManager::AbstractPluginFactory::Pointer first_factory = factory_list.front();
  TestPluginManager::AbstractPluginFactory::Pointer second_factory = factory_list.back();

  // because order of factory list is not determined:
  CPPUNIT_ASSERT(
      (first_factory->getId() == "Morning" && second_factory->getId() == "Evening") ||
      (first_factory->getId() == "Evening" && second_factory->getId() == "Morning")
      );

}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(PluginManager_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

