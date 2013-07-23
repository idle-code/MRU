#include "InputPlugin_test.hpp"
#include "plugins/input/BoostInput/BoostInput.hpp"
#include <cppunit/ui/text/TestRunner.h>

namespace mru
{

class BoostInput_tests : public InputPlugin_tests {
public:
  InputPlugin *
  getInputPlugin(void)
  {
    InputPlugin *plugin = new BoostInput;
    CPPUNIT_ASSERT(plugin != NULL);
    return plugin;
  }

  void
  createDirectory(const FilePath &path)
  {
    bfs::create_directories(path);
  }

  void
  removeDirectory(const FilePath &path)
  {
    if (bfs::exists(path))
      bfs::remove_all(path);
  }

  CPPUNIT_TEST_SUB_SUITE(BoostInput_tests, InputPlugin_tests);
  CPPUNIT_TEST_SUITE_END();
};

} /* namespace mru */

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(BoostInput_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

