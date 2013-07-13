#include "InputPlugin_test.hpp"
#include "plugins/input/BoostInputPlugin/BoostInputPlugin.hpp"
#include <cppunit/ui/text/TestRunner.h>

namespace mru
{

class BoostInputPlugin_tests : public InputPlugin_tests {
public:
  InputPlugin* getInputPlugin(void)
  {
    InputPlugin *plugin = new BoostInputPlugin;
    CPPUNIT_ASSERT(plugin != NULL);
    return plugin;
  }

  CPPUNIT_TEST_SUB_SUITE(BoostInputPlugin_tests, InputPlugin_tests);
  CPPUNIT_TEST_SUITE_END();
};

} /* namespace mru */

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(BoostInputPlugin_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

