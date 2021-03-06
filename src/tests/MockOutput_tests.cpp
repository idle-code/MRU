#include "OutputPlugin_tests.hpp"
#include "MockOutput.hpp"
#include <cppunit/ui/text/TestRunner.h>

namespace mru
{

class MockOutput_tests : public OutputPlugin_tests {
public:
  MockOutput *
  getOutputPlugin(void)
  {
    MockOutput *plugin = new MockOutput();
    CPPUNIT_ASSERT(plugin != NULL);
    return plugin;
  }

  void
  createFile(const FilePath &path)
  {
    assert(output_plugin != NULL);
    ((MockOutput*)output_plugin)->createFile(path);
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

