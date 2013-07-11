#include "InputPlugin_test.hpp"
#include <cppunit/ui/text/TestRunner.h>


InputPlugin_tests::InputPlugin_tests(void)
{
  test_directory = bfs::current_path() / "files";

  input_plugin = new InputPluginTestClass;
  CPPUNIT_ASSERT(input_plugin != NULL);
}

InputPlugin_tests::~InputPlugin_tests(void)
{
  CPPUNIT_ASSERT(input_plugin != NULL);
  delete input_plugin;
}

/* ------------------------------------------------------------------------- */

void
InputPlugin_tests::construction(void)
{
  FileIterator::Pointer file_iterator = input_plugin->getFileIterator("./files");
  CPPUNIT_ASSERT(file_iterator != NULL);

  file_iterator = input_plugin->getFileIterator("./non_existing");
  CPPUNIT_ASSERT(file_iterator == NULL);
}

void
InputPlugin_tests::single_level_files(void) 
{
  FileIterator::Pointer file_iterator = input_plugin->getFileIterator("./files");
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
}

void
InputPlugin_tests::multi_level(void) 
{

}

void
InputPlugin_tests::regex_filter(void) 
{

}

void
InputPlugin_tests::only_directories(void) 
{

}

void
InputPlugin_tests::only_files(void) 
{

}

void
InputPlugin_tests::directories_and_files(void) 
{

}

void
InputPlugin_tests::sorting(void) 
{

}

void
InputPlugin_tests::filename(void) 
{

}

void
InputPlugin_tests::directory(void) 
{

}

void
InputPlugin_tests::absolute_filename(void) 
{

}

void
InputPlugin_tests::absolute_directory(void) 
{

}

void
InputPlugin_tests::new_path(void) 
{

}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(InputPlugin_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

