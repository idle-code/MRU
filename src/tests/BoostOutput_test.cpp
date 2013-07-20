#include "OutputPlugin_test.hpp"
#include "plugins/output/BoostOutput/BoostOutput.hpp"
#include <cppunit/ui/text/TestRunner.h>

namespace mru
{

class BoostOutput_tests : public OutputPlugin_tests {
public:
  OutputPlugin* getOutputPlugin(void)
  {
    OutputPlugin *plugin = new BoostOutput;
    CPPUNIT_ASSERT(plugin != NULL);
    return plugin;
  }

  void
  createFile(const FilePath &a_path)
  {
    std::ofstream empty_file(a_path.string().c_str());
    empty_file << "File generated for tests" << std::endl;
    empty_file.close();
  }

  CPPUNIT_TEST_SUB_SUITE(BoostOutput_tests, OutputPlugin_tests);
  CPPUNIT_TEST_SUITE_END();
};

} /* namespace mru */

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(BoostOutput_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

