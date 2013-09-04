#include "MruCore_tests.hpp"

void
MruCore_tests::without_start(void)
{
  MruCore::Pointer core = boost::make_shared<MruCore>();
}

void
MruCore_tests::without_arguments(void)
{
  MruCore::Pointer core = boost::make_shared<MruCore>();

  int result = core->start(0, NULL);
  
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MruCore_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

