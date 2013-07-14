#ifndef INPUT_PLUGIN_TEST_HPP
#define INPUT_PLUGIN_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#define PLUGIN_HOST
#include "plugins/InputPlugin.hpp"

using namespace CppUnit;
using namespace mru;

class InputPlugin_tests : public TestCase {
public:
  InputPlugin_tests(void);
  virtual InputPlugin* getInputPlugin(void) = 0;
  void setUp(void);
  void tearDown(void);
private:
  FilePath test_directory;
  InputPlugin *input_plugin;
public:
  void construction(void);
  void non_existing_exception(void);
  void bad_config_exception(void);
  void flat_files(void);
  void flat_directories(void);
  void recursive_files(void);
  void recursive_directories(void);

  CPPUNIT_TEST_SUITE(InputPlugin_tests);
    CPPUNIT_TEST(construction);
    CPPUNIT_TEST_EXCEPTION(non_existing_exception, InputPluginException);
    CPPUNIT_TEST_EXCEPTION(bad_config_exception, InputPluginException);
    CPPUNIT_TEST(flat_files);
    CPPUNIT_TEST(flat_directories);
    CPPUNIT_TEST(recursive_files);
    CPPUNIT_TEST(recursive_directories);
  CPPUNIT_TEST_SUITE_END_ABSTRACT();
};

#endif /* INPUT_PLUGIN_TEST_HPP */

