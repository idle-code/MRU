
#include "OutputPlugin_test.hpp"
#include "MockOutput.hpp"
#include <cppunit/ui/text/TestRunner.h>

namespace mru
{

class MockOutput_tests : public OutputPlugin_tests {
public:
  OutputPlugin *
  getOutputPlugin(void)
  {
    OutputPlugin *plugin = new MockOutput();
    CPPUNIT_ASSERT(plugin != NULL);
    return plugin;
  }

  void
  createFile(const FilePath &a_path)
  {
    assert(output_plugin != NULL);
    ((MockOutput*)output_plugin)->createFile(a_path);
  }

  CPPUNIT_TEST_SUB_SUITE(MockOutput_tests, OutputPlugin_tests);
  CPPUNIT_TEST_SUITE_END();
};

} /* namespace mru */

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MockOutput_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

