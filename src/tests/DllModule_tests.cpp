#include "DllModule_tests.hpp"

#include "BsdDllModule.hpp"
#define TEST_MODULE "./libtest_module.so"

void
DllModule_tests::setUp(void)
{
  module = BsdDllModule::create();
  CPPUNIT_ASSERT(!module->isLoaded());
}

/* ------------------------------------------------------------------------- */

void
DllModule_tests::load_nonexisting(void)
{
  module->load("./some_file.so");
}

void
DllModule_tests::load_existing_non_dll(void)
{
  module->load("./DllModule_tests.hpp");

}

void
DllModule_tests::load_existing(void)
{
  module->load(TEST_MODULE);
  CPPUNIT_ASSERT(module->isLoaded());

}

void
DllModule_tests::unload(void)
{
  module->load(TEST_MODULE);
  CPPUNIT_ASSERT(module->isLoaded());

  module->unLoad();
  CPPUNIT_ASSERT(!module->isLoaded());
}

void
DllModule_tests::unload_not_loaded(void)
{
  module->unLoad();
  CPPUNIT_ASSERT(!module->isLoaded());
}

typedef int (*HelloFunction)(void);

void
DllModule_tests::load_nonexisting_symbol(void)
{
  module->load(TEST_MODULE);
  CPPUNIT_ASSERT(module->isLoaded());
  
  HelloFunction goodbye = module->get<HelloFunction>("goodbye");
  CPPUNIT_ASSERT(goodbye == NULL);
}

void
DllModule_tests::load_symbol(void)
{
  module->load(TEST_MODULE);
  CPPUNIT_ASSERT(module->isLoaded());
  
  HelloFunction hello = module->get<HelloFunction>("hello");
  CPPUNIT_ASSERT(hello != NULL);

  CPPUNIT_ASSERT_EQUAL(321, hello());
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(DllModule_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

