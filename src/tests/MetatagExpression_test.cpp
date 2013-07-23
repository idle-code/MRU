#include "MetatagExpression_test.hpp"
#include <cppunit/ui/text/TestRunner.h>

void
MetatagExpression_tests::construction(void)
{

}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MetatagExpression_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

