#include "InputPlugin_test.hpp"
#include "SortingFileIterator.hpp"

InputPlugin_tests::InputPlugin_tests(void)
  : input_plugin(NULL)
{
  test_directory = bfs::current_path() / "files";
}

void
InputPlugin_tests::createFile(const FilePath &a_path)
{
  createDirectory(a_path.parent_path());
  std::ofstream empty_file(a_path.string().c_str());
  empty_file << "File generated for tests" << std::endl;
  empty_file.close();
}

void
InputPlugin_tests::setUp(void)
{
  createDirectory(test_directory);

  input_plugin = getInputPlugin();
  CPPUNIT_ASSERT(input_plugin != NULL);
  input_plugin->includeFiles(true);
  input_plugin->includeDirectories(false);
  input_plugin->searchRecursively(false);

  // default configuration
  CPPUNIT_ASSERT_EQUAL(true, input_plugin->includeFiles());
  CPPUNIT_ASSERT_EQUAL(false, input_plugin->includeDirectories());
  CPPUNIT_ASSERT_EQUAL(false, input_plugin->searchRecursively());
}

void
InputPlugin_tests::tearDown(void)
{
  CPPUNIT_ASSERT(input_plugin != NULL);
  delete input_plugin;
  input_plugin = NULL;

  removeDirectory(test_directory);
}

/* ------------------------------------------------------------------------- */

void
InputPlugin_tests::construction(void)
{
  FileIterator::Pointer file_iterator = input_plugin->getFileIterator(test_directory);
  CPPUNIT_ASSERT(file_iterator != NULL);
  CPPUNIT_ASSERT(file_iterator->atEnd());
}

void
InputPlugin_tests::non_existing_exception(void)
{
  FileIterator::Pointer file_iterator = input_plugin->getFileIterator("./non_existing"); //throw InputPluginException
}

void
InputPlugin_tests::bad_config_exception(void)
{
  input_plugin->includeFiles(false);
  input_plugin->includeDirectories(false);
  FileIterator::Pointer file_iterator = input_plugin->getFileIterator(test_directory); //throw InputPluginException
}

struct SimpleComparer : public SortingFileIterator::SortComparator
{
  int operator()(const FilePath &a_path_a, const FilePath &a_path_b)
  {
    return a_path_a < a_path_b;
  }
};

void
InputPlugin_tests::flat_files(void) 
{
  std::list<FilePath> file_list;
  file_list.push_back(test_directory / "a");
  file_list.push_back(test_directory / "b");
  file_list.push_back(test_directory / "bb_cc_aa");
  file_list.push_back(test_directory / "c");
  file_list.push_back(test_directory / "mru.log");
  file_list.push_back(test_directory / "other_app.log");

  std::list<FilePath>::iterator i = file_list.begin();
  for(; i != file_list.end(); ++i) {
    createFile(*i);
  }

  FileIterator::Pointer file_iterator = input_plugin->getFileIterator(test_directory);
  CPPUNIT_ASSERT(file_iterator != NULL);
  file_iterator = SortingFileIterator::wrap(file_iterator, new SimpleComparer());
  CPPUNIT_ASSERT(file_iterator != NULL);
  
  CPPUNIT_ASSERT(!file_iterator->atEnd());
  i = file_list.begin();
  for(; !file_iterator->atEnd() && i != file_list.end(); file_iterator->next(), ++i) {
    CPPUNIT_ASSERT(i != file_list.end());
    CPPUNIT_ASSERT_EQUAL(*i, file_iterator->getFilePath());
  }
  CPPUNIT_ASSERT(i == file_list.end());
  CPPUNIT_ASSERT(file_iterator->atEnd());
}

void
InputPlugin_tests::flat_directories(void) 
{
  std::list<FilePath> dir_list;
  dir_list.push_back(test_directory / "dirA");
  dir_list.push_back(test_directory / "dirB");
  dir_list.push_back(test_directory / "dirC");

  std::list<FilePath>::iterator i = dir_list.begin();
  for(; i != dir_list.end(); ++i) {
    createDirectory(*i);
  }

  input_plugin->includeFiles(false);
  input_plugin->includeDirectories(true);

  FileIterator::Pointer file_iterator = input_plugin->getFileIterator(test_directory);
  CPPUNIT_ASSERT(file_iterator != NULL);
  file_iterator = SortingFileIterator::wrap(file_iterator, new SimpleComparer());
  CPPUNIT_ASSERT(file_iterator != NULL);

  CPPUNIT_ASSERT(!file_iterator->atEnd());
  i = dir_list.begin();
  for(; !file_iterator->atEnd() && i != dir_list.end(); file_iterator->next(), ++i) {
    CPPUNIT_ASSERT(i != dir_list.end());
    CPPUNIT_ASSERT_EQUAL(*i, file_iterator->getFilePath());
  }
  CPPUNIT_ASSERT(i == dir_list.end());
  CPPUNIT_ASSERT(file_iterator->atEnd());
}

void
InputPlugin_tests::recursive_files(void) 
{
  std::list<FilePath> file_list;
  file_list.push_back(test_directory / "a");
  file_list.push_back(test_directory / "b");
  file_list.push_back(test_directory / "bb_cc_aa");
  file_list.push_back(test_directory / "c");
  file_list.push_back(test_directory / "dirA" / "text_file1.txt");
  file_list.push_back(test_directory / "dirA" / "text_file2.txt");
  file_list.push_back(test_directory / "dirA" / "text_file3.txt");
  file_list.push_back(test_directory / "dirB" / "aa_bb_cc");
  file_list.push_back(test_directory / "dirB" / "mru.log");
  file_list.push_back(test_directory / "dirB" / "spam" / "bar.png");
  file_list.push_back(test_directory / "dirB" / "spam" / "foo.avi");
  file_list.push_back(test_directory / "dirC" / "bb_aa_cc");
  file_list.push_back(test_directory / "dirC" / "other_app.log");
  file_list.push_back(test_directory / "mru.log");
  file_list.push_back(test_directory / "other_app.log");

  std::list<FilePath>::iterator i = file_list.begin();
  for(; i != file_list.end(); ++i) {
    createFile(*i);
  }

  input_plugin->searchRecursively(true);

  FileIterator::Pointer file_iterator = input_plugin->getFileIterator(test_directory);
  CPPUNIT_ASSERT(file_iterator != NULL);
  file_iterator = SortingFileIterator::wrap(file_iterator, new SimpleComparer());
  CPPUNIT_ASSERT(file_iterator != NULL);
  
  CPPUNIT_ASSERT(!file_iterator->atEnd());
  i = file_list.begin();
  for(; !file_iterator->atEnd() && i != file_list.end(); file_iterator->next(), ++i) {
    CPPUNIT_ASSERT(i != file_list.end());
    CPPUNIT_ASSERT_EQUAL(*i, file_iterator->getFilePath());
  }
  CPPUNIT_ASSERT(i == file_list.end());
  CPPUNIT_ASSERT(file_iterator->atEnd());
}

void
InputPlugin_tests::recursive_directories(void) 
{
  std::list<FilePath> dir_list;
  dir_list.push_back(test_directory / "dirA");
  dir_list.push_back(test_directory / "dirB");
  dir_list.push_back(test_directory / "dirB" / "spam");
  dir_list.push_back(test_directory / "dirC");

  std::list<FilePath>::iterator i = dir_list.begin();
  for(; i != dir_list.end(); ++i) {
    createDirectory(*i);
  }

  input_plugin->includeFiles(false);

  input_plugin->includeDirectories(true);
  input_plugin->searchRecursively(true);

  FileIterator::Pointer file_iterator = input_plugin->getFileIterator(test_directory);
  CPPUNIT_ASSERT(file_iterator != NULL);
  file_iterator = SortingFileIterator::wrap(file_iterator, new SimpleComparer());
  CPPUNIT_ASSERT(file_iterator != NULL);

  CPPUNIT_ASSERT(!file_iterator->atEnd());
  i = dir_list.begin();
  for(; !file_iterator->atEnd() && i != dir_list.end(); file_iterator->next(), ++i) {
    CPPUNIT_ASSERT(i != dir_list.end());
    CPPUNIT_ASSERT_EQUAL(*i, file_iterator->getFilePath());
  }
  CPPUNIT_ASSERT(i == dir_list.end());
  CPPUNIT_ASSERT(file_iterator->atEnd());
}

