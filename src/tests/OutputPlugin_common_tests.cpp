#include "OutputPlugin_tests.hpp"

OutputPlugin_tests::OutputPlugin_tests(void)
  : output_plugin(NULL)
{
  test_directory = bfs::current_path() / "files";
}

void
OutputPlugin_tests::setUp(void)
{
  output_plugin = getOutputPlugin();
  CPPUNIT_ASSERT(output_plugin != NULL);
  output_plugin->createNewPath(true);
  output_plugin->createDirectory(test_directory);
  CPPUNIT_ASSERT(output_plugin->exists(test_directory));
  output_plugin->createNewPath(false);
  // default settings:
  CPPUNIT_ASSERT(!output_plugin->overrideTarget());
  CPPUNIT_ASSERT(!output_plugin->createNewPath());
}

void
OutputPlugin_tests::tearDown(void)
{
  CPPUNIT_ASSERT(output_plugin != NULL);
  CPPUNIT_ASSERT(output_plugin->exists(test_directory));
  output_plugin->removeDirectory(test_directory);
  delete output_plugin;
  output_plugin = NULL;
}

/* ------------------------------------------------------------------------- */

void
OutputPlugin_tests::exists_file(void)
{
  createFile(test_directory / "test_file");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "test_file"));
}

void
OutputPlugin_tests::exists_directory(void)
{
  output_plugin->createDirectory(test_directory / "test_dir");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "test_dir"));
}

void
OutputPlugin_tests::exists_no_target(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "some_strange_file"));
}

void
OutputPlugin_tests::exists_empty(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(""));
}

/* ------------------------------------------------------------------------- */

void
OutputPlugin_tests::create_directory(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "created_directory"));
  
  output_plugin->createDirectory(test_directory / "created_directory");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "created_directory"));
}

void
OutputPlugin_tests::create_directory_no_target_path_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part"));
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part" / "created_directory"));
  
  output_plugin->createDirectory(test_directory / "directory_part" / "created_directory"); //throw OutputPluginException
}

void
OutputPlugin_tests::create_directory_no_target_path_exists_create_new(void)
{
  output_plugin->createNewPath(true);
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part"));
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part" / "created_directory"));
  
  output_plugin->createDirectory(test_directory / "directory_part" / "created_directory"); //throw OutputPluginException

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "directory_part"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "directory_part" / "created_directory"));
}

void
OutputPlugin_tests::create_directory_target_exists(void)
{
  output_plugin->createDirectory(test_directory / "dirA");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "dirA"));

  output_plugin->createDirectory(test_directory / "dirA"); //throw OutputPluginException
}

void
OutputPlugin_tests::create_directory_target_file_exists(void)
{
  createFile(test_directory / "a");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));

  output_plugin->createDirectory(test_directory / "a"); //throw OutputPluginException
}

void
OutputPlugin_tests::create_directory_target_exists_override(void)
{
  output_plugin->createNewPath(true);
  CPPUNIT_ASSERT(output_plugin->createNewPath());
  createFile(test_directory / "a");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));

  output_plugin->createDirectory(test_directory / "a"); //throw OutputPluginException
}

void
OutputPlugin_tests::remove_directory(void)
{
  output_plugin->createDirectory(test_directory / "created_directory");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "created_directory"));

  output_plugin->removeDirectory(test_directory / "created_directory");
  
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "created_directory"));
}

void
OutputPlugin_tests::remove_directory_no_source_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "nonexisting_directory"));

  output_plugin->removeDirectory(test_directory / "nonexisting_directory"); //throw OutputPluginException
}

