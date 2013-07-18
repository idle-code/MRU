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
  virtual void createFile(const FilePath &a_path) = 0;
  void setUp(void);
  void tearDown(void);
protected:
  FilePath test_directory;
  OutputPlugin *output_plugin;
public:
  void create_directory(void);
  void create_existing_directory(void);
  void create_existing_file(void);
  void remove_directory(void);
  void remove_nonexisting_directory(void);
  
  // ModeRename tests
  void move_mode_target_file_exists(void);
  void move_mode_target_file_exists_override(void);
  void move_mode_no_target_file_exists(void);

  void move_mode_target_directory_exists(void);
  void move_mode_target_directory_exists_override(void);
  void move_mode_no_target_directory_exists(void);

  void move_mode_no_source_file_exists(void);
  void move_mode_no_source_directory_exists(void);

  void move_mode_(void);
  
  // ModeCopy tests
  //TODO
  
  // ModeLink tests
  //TODO

  //void nonexisting_source_exception(void);
  //void existing_target_exception(void);
  //void existing_target_noexception(void);
  //void same_source_and_target(void);
  //void file_move(void);
  //void directory_move(void);
  //void full_move(void);


  CPPUNIT_TEST_SUITE(OutputPlugin_tests);
    CPPUNIT_TEST(create_directory);
    CPPUNIT_TEST_EXCEPTION(create_existing_directory, OutputPluginException);
    CPPUNIT_TEST_EXCEPTION(create_existing_file, OutputPluginException);
    CPPUNIT_TEST(remove_directory);
    CPPUNIT_TEST_EXCEPTION(remove_nonexisting_directory, OutputPluginException);
    // ModeRename
    CPPUNIT_TEST_EXCEPTION(move_mode_target_file_exists, OutputPluginException);
    CPPUNIT_TEST(move_mode_target_file_exists_override);
    CPPUNIT_TEST(move_mode_no_target_file_exists);
    CPPUNIT_TEST_EXCEPTION(move_mode_target_directory_exists, OutputPluginException);
    CPPUNIT_TEST(move_mode_target_directory_exists_override);
    CPPUNIT_TEST(move_mode_no_target_directory_exists);
    CPPUNIT_TEST_EXCEPTION(move_mode_no_source_file_exists, OutputPluginException);
    CPPUNIT_TEST_EXCEPTION(move_mode_no_source_directory_exists, OutputPluginException);
    // ModeCopy
    // ModeLink
    //CPPUNIT_TEST_EXCEPTION(nonexisting_source_exception, OutputPluginException);
    //CPPUNIT_TEST_EXCEPTION(existing_target_exception, OutputPluginException);
    //CPPUNIT_TEST(existing_target_noexception);
  CPPUNIT_TEST_SUITE_END_ABSTRACT();
};

#endif /* OUTPUT_PLUGIN_TEST_HPP */

