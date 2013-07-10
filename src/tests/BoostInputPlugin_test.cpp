#include "BoostInputPlugin_test.hpp"
#include <cppunit/ui/text/TestRunner.h>


BoostInputPlugin_tests::BoostInputPlugin_tests(void)
{
  FO("BoostInputPlugin_tests::BoostInputPlugin_tests(void)");
  InputPluginManager::set_instance(new InputPluginManager("InputPlugin"));
  InputPluginManager::get_instance()->load_module("../plugins/input/BoostInputPlugin/libBoostInputPlugin.so");

  test_directory = bfs::current_path() / "files";
}

void
BoostInputPlugin_tests::setUp(void)
{
  input_plugin = InputPluginManager::get_instance()->create_plugin("BoostInputPlugin");
  assert(input_plugin != NULL);
}

void
BoostInputPlugin_tests::tearDown(void)
{
  InputPluginManager::get_instance()->destroy_plugin(input_plugin);
  input_plugin = NULL;
}

/* ------------------------------------------------------------------------- */

void
BoostInputPlugin_tests::construction(void)
{
  FileIterator *file_iterator = input_plugin->getFileIterator("./files", FileIterator::SortComparator());
  CPPUNIT_ASSERT(file_iterator != NULL);

  delete file_iterator;
}

void
BoostInputPlugin_tests::single_level_files(void) 
{
  FileIterator *file_iterator = input_plugin->getFileIterator("./files", FileIterator::SortComparator());
  CPPUNIT_ASSERT(file_iterator != NULL);

  CPPUNIT_ASSERT_EQUAL(test_directory / "a", file_iterator->getFilePath());
  CPPUNIT_ASSERT(file_iterator->next());
  CPPUNIT_ASSERT_EQUAL(test_directory / "b", file_iterator->getFilePath());
  CPPUNIT_ASSERT(file_iterator->next());
  CPPUNIT_ASSERT_EQUAL(test_directory / "bb_cc_aa", file_iterator->getFilePath());
  CPPUNIT_ASSERT(file_iterator->next());
  CPPUNIT_ASSERT_EQUAL(test_directory / "c", file_iterator->getFilePath());
  CPPUNIT_ASSERT(file_iterator->next());
  CPPUNIT_ASSERT_EQUAL(test_directory / "mru.log", file_iterator->getFilePath());
  CPPUNIT_ASSERT(file_iterator->next());
  CPPUNIT_ASSERT_EQUAL(test_directory / "other_app.log", file_iterator->getFilePath());
  CPPUNIT_ASSERT(!file_iterator->next());

  delete file_iterator;
}

void
BoostInputPlugin_tests::multi_level(void) 
{

}

void
BoostInputPlugin_tests::regex_filter(void) 
{

}

void
BoostInputPlugin_tests::only_directories(void) 
{

}

void
BoostInputPlugin_tests::only_files(void) 
{

}

void
BoostInputPlugin_tests::directories_and_files(void) 
{

}

void
BoostInputPlugin_tests::sorting(void) 
{

}

void
BoostInputPlugin_tests::filename(void) 
{

}

void
BoostInputPlugin_tests::directory(void) 
{

}

void
BoostInputPlugin_tests::absolute_filename(void) 
{

}

void
BoostInputPlugin_tests::absolute_directory(void) 
{

}

void
BoostInputPlugin_tests::new_path(void) 
{

}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(BoostInputPlugin_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

