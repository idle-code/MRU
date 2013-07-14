
#ifndef OUTPUT_PLUGIN_TEST_HPP
#define OUTPUT_PLUGIN_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#define PLUGIN_HOST
#include "plugins/OutputPlugin.hpp"

using namespace CppUnit;
using namespace mru;

class OutputPlugin_tests : public TestCase {
public:
  OutputPlugin_tests(void);
  virtual OutputPlugin* getOutputPlugin(void) = 0;
  void setUp(void);
  void tearDown(void);
private:
  FilePath test_directory;
  OutputPlugin *output_plugin;
public:
  void construction(void);
  void existing_target_exception(void);
  void nonexisting_source_exception(void);
  void bad_filename_excetpion(void);
  void same_source_and_target(void);
  void file_rename(void);
  void directory_rename(void);
  void full_rename(void);

  //move/replace/follow symlinks options tests

  CPPUNIT_TEST_SUITE(OutputPlugin_tests);
    CPPUNIT_TEST(construction);
  CPPUNIT_TEST_SUITE_END_ABSTRACT();
};

#endif /* OUTPUT_PLUGIN_TEST_HPP */

