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
  virtual void createFile(const FilePath &path) = 0;
  void setUp(void);
  void tearDown(void);
protected:
  FilePath test_directory;
  OutputPlugin *output_plugin;
public:
  void exists_file(void);
  void exists_directory(void);
  void exists_no_target(void);
  void exists_empty(void);
  
  // directory operations
  void create_directory(void);
  void create_directory_no_target_path_exists(void);
  void create_directory_no_target_path_exists_create_new(void);
  void create_directory_target_exists(void);
  void create_directory_target_file_exists(void);
  void create_directory_target_exists_override(void);
  void remove_directory(void);
  void remove_directory_no_source_exists(void);
  
  // move tests
  void move_target_exists(void);
  void move_target_exists_override(void);
  void move_no_target_exists(void);
  void move_no_source_exists(void);
  void move_no_target_path_exists(void);
  void move_no_target_path_exists_create_new(void);
  
  // copy tests
  void copy_target_exists(void);
  void copy_target_exists_override(void);
  void copy_no_target_exists(void);
  void copy_no_source_exists(void);
  void copy_no_target_path_exists(void);
  void copy_no_target_path_exists_create_new(void);
  
  // link tests
  void link_target_exists(void);
  void link_target_exists_override(void);
  void link_no_target_exists(void);
  void link_no_source_exists(void);
  void link_no_target_path_exists(void);
  void link_no_target_path_exists_create_new(void);

  void resolveLink_target_exists(void);
  void resolveLink_not_link_target_exists(void);
  void resolveLink_no_target_exists(void);

#if 1
  CPPUNIT_TEST_SUITE(OutputPlugin_tests);
    // file creation (for test only)
    //CPPUNIT_TEST_EXCEPTION(create_existing_file, OutputPlugin::Exception);
    CPPUNIT_TEST(exists_file);
    CPPUNIT_TEST(exists_directory);
    CPPUNIT_TEST(exists_no_target);
    CPPUNIT_TEST(exists_empty);
    // directory creation
    CPPUNIT_TEST(create_directory);
    CPPUNIT_TEST_EXCEPTION(create_directory_no_target_path_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(create_directory_no_target_path_exists_create_new);
    CPPUNIT_TEST_EXCEPTION(create_directory_target_exists, OutputPlugin::Exception);
    CPPUNIT_TEST_EXCEPTION(create_directory_target_file_exists, OutputPlugin::Exception);
    CPPUNIT_TEST_EXCEPTION(create_directory_target_exists_override, OutputPlugin::Exception);
    CPPUNIT_TEST(remove_directory);
    CPPUNIT_TEST_EXCEPTION(remove_directory_no_source_exists, OutputPlugin::Exception);
    // move
    CPPUNIT_TEST_EXCEPTION(move_target_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(move_target_exists_override);
    CPPUNIT_TEST(move_no_target_exists);
    CPPUNIT_TEST_EXCEPTION(move_no_source_exists, OutputPlugin::Exception);
    CPPUNIT_TEST_EXCEPTION(move_no_target_path_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(move_no_target_path_exists_create_new);
    // copy
    CPPUNIT_TEST_EXCEPTION(copy_target_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(copy_target_exists_override);
    CPPUNIT_TEST(copy_no_target_exists);
    CPPUNIT_TEST_EXCEPTION(copy_no_source_exists, OutputPlugin::Exception);
    CPPUNIT_TEST_EXCEPTION(copy_no_target_path_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(copy_no_target_path_exists_create_new);
    // link
    CPPUNIT_TEST_EXCEPTION(link_target_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(link_target_exists_override);
    CPPUNIT_TEST(link_no_target_exists);
    CPPUNIT_TEST_EXCEPTION(link_no_source_exists, OutputPlugin::Exception);
    CPPUNIT_TEST_EXCEPTION(link_no_target_path_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(link_no_target_path_exists_create_new);
    
    CPPUNIT_TEST(resolveLink_target_exists);
    CPPUNIT_TEST_EXCEPTION(resolveLink_not_link_target_exists, OutputPlugin::Exception);
    CPPUNIT_TEST_EXCEPTION(resolveLink_no_target_exists, OutputPlugin::Exception);
  CPPUNIT_TEST_SUITE_END_ABSTRACT();
#else
  CPPUNIT_TEST_SUITE(OutputPlugin_tests);
    //CPPUNIT_TEST_EXCEPTION(create_directory_no_target_path_exists, OutputPlugin::Exception);
    CPPUNIT_TEST(create_directory_no_target_path_exists_create_new);
  CPPUNIT_TEST_SUITE_END_ABSTRACT();
#endif
};

#endif /* OUTPUT_PLUGIN_TEST_HPP */

