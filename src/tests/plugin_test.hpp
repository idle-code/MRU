#ifndef PLUGIN_TEST_HPP
#define PLUGIN_TEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

//#include "../plugin_manager/plugin_manager.hpp"
#include "plugin_manager.hpp"

using namespace CppUnit;
using namespace mru;

class plugin_tests : public TestCase {
public:
  void construct(void);
  void load(void);
  void unload(void);
  void lookup(void);

  CPPUNIT_TEST_SUITE(plugin_tests);
    CPPUNIT_TEST(construct);
    CPPUNIT_TEST(load);
    CPPUNIT_TEST(unload);
    CPPUNIT_TEST(lookup);
  CPPUNIT_TEST_SUITE_END();
};

#endif /* PLUGIN_TEST_HPP */

