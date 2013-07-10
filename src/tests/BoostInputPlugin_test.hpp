#ifndef BOOST_INPUT_PLUGIN_TEST_HPP
#define BOOST_INPUT_PLUGIN_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#define PLUGIN_HOST
#include "plugins/InputPlugin.hpp"

using namespace CppUnit;
using namespace mru;

class BoostInputPlugin_tests : public TestCase {
public:
  BoostInputPlugin_tests(void);
  void setUp(void);
  void tearDown(void);
private:
  InputPlugin *input_plugin;
  FilePath test_directory;
public:
  void construction(void);
  void single_level_files(void);
  void multi_level(void);
  void regex_filter(void);
  void only_directories(void);
  void only_files(void);
  void directories_and_files(void);
  void sorting(void);
  void filename(void);
  void directory(void);
  void absolute_filename(void);
  void absolute_directory(void);
  void new_path(void);

  CPPUNIT_TEST_SUITE(BoostInputPlugin_tests);
    CPPUNIT_TEST(construction);
    CPPUNIT_TEST(single_level_files);
    //CPPUNIT_TEST(multi_level);
    //CPPUNIT_TEST(regex_filter);
    //CPPUNIT_TEST(only_directories);
    //CPPUNIT_TEST(only_files);
    //CPPUNIT_TEST(directories_and_files);
    //CPPUNIT_TEST(sorting);
    //CPPUNIT_TEST(filename);
    //CPPUNIT_TEST(directory);
    //CPPUNIT_TEST(absolute_filename);
    //CPPUNIT_TEST(absolute_directory);
    //CPPUNIT_TEST(new_path);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* BOOST_INPUT_PLUGIN_TEST_HPP */

