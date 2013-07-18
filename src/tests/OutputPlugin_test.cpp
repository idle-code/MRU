#include "OutputPlugin_test.hpp"

#include "plugins/InputPlugin.hpp"
#include "SortingFileIterator.hpp"

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
  // default settings:
  CPPUNIT_ASSERT(!output_plugin->overwriteTarget());
  CPPUNIT_ASSERT(!output_plugin->createNewPath());
  CPPUNIT_ASSERT_EQUAL(OutputPlugin::ModeRename, output_plugin->getRenameMode());
  // prevent from changing files:
  output_plugin->setRenameMode(OutputPlugin::ModeNone);
  CPPUNIT_ASSERT_EQUAL(OutputPlugin::ModeNone, output_plugin->getRenameMode());
}

void
OutputPlugin_tests::tearDown(void)
{
  CPPUNIT_ASSERT(output_plugin != NULL);
  delete output_plugin;
  output_plugin = NULL;
}

/* ------------------------------------------------------------------------- */

void
OutputPlugin_tests::create_directory(void)
{
  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "created_directory"));
  
  output_plugin->createDirectory(test_directory / "created_directory");

  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "created_directory"));
}

void
OutputPlugin_tests::create_existing_directory(void)
{
  output_plugin->createDirectory(test_directory / "dirA");
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirA"));

  output_plugin->createDirectory(test_directory / "dirA"); //throw OutputPluginException
}

void
OutputPlugin_tests::create_existing_file(void)
{
  createFile(test_directory / "a");
  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "a"));

  output_plugin->createDirectory(test_directory / "a"); //throw OutputPluginException
}

void
OutputPlugin_tests::remove_directory(void)
{
  output_plugin->createDirectory(test_directory / "created_directory");
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "created_directory"));

  output_plugin->removeDirectory(test_directory / "created_directory");
  
  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "created_directory"));
}

void
OutputPlugin_tests::remove_nonexisting_directory(void)
{
  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "nonexisting_directory"));

  output_plugin->removeDirectory(test_directory / "nonexisting_directory"); //throw OutputPluginException
}

/* ------------------------------------------------------------------------- */

void
OutputPlugin_tests::move_mode_target_file_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->overwriteTarget());

  createFile(test_directory / "b");
  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "b"));

  output_plugin->moveFile(test_directory / "a", test_directory / "b"); //throw OutputPluginException
}

void
OutputPlugin_tests::move_mode_target_file_exists_override(void)
{
  output_plugin->overwriteTarget(true);
  CPPUNIT_ASSERT(output_plugin->overwriteTarget());

  createFile(test_directory / "a");
  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "a"));
  createFile(test_directory / "b");
  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "b"));

  output_plugin->moveFile(test_directory / "a", test_directory / "b");

  CPPUNIT_ASSERT(!output_plugin->fileExists(test_directory / "a"));
  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "b"));
}

void
OutputPlugin_tests::move_mode_no_target_file_exists(void)
{
  createFile(test_directory / "a");
  CPPUNIT_ASSERT(!output_plugin->fileExists(test_directory / "new_a"));
  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "a"));

  output_plugin->moveFile(test_directory / "a", test_directory / "new_a");

  CPPUNIT_ASSERT(output_plugin->fileExists(test_directory / "new_a"));
  CPPUNIT_ASSERT(!output_plugin->fileExists(test_directory / "a"));
}

void
OutputPlugin_tests::move_mode_target_directory_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->overwriteTarget());

  output_plugin->createDirectory(test_directory / "dirA");
  output_plugin->createDirectory(test_directory / "dirB");
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirA"));
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirB"));

  output_plugin->moveDirectory(test_directory / "dirA", test_directory / "dirB"); //throw OutputPluginException
}

void
OutputPlugin_tests::move_mode_target_directory_exists_override(void)
{
  output_plugin->overwriteTarget(true);
  CPPUNIT_ASSERT(output_plugin->overwriteTarget());

  output_plugin->createDirectory(test_directory / "dirA");
  output_plugin->createDirectory(test_directory / "dirB");
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirA"));
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirB"));

  output_plugin->moveDirectory(test_directory / "dirA", test_directory / "dirB");

  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "dirA"));
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirB"));
}

void
OutputPlugin_tests::move_mode_no_target_directory_exists(void)
{
  output_plugin->createDirectory(test_directory / "dirA");
  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "dirA"));
  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "new_dirA"));

  output_plugin->moveDirectory(test_directory / "dirA", test_directory / "new_dirA");

  CPPUNIT_ASSERT(output_plugin->directoryExists(test_directory / "new_dirA"));
  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "dirA"));
}

void
OutputPlugin_tests::move_mode_no_source_file_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->fileExists(test_directory / "unknown"));

  output_plugin->moveFile(test_directory / "unknown", test_directory / "new_unknown"); //throw OutputPluginException
}

void
OutputPlugin_tests::move_mode_no_source_directory_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->directoryExists(test_directory / "unknown"));

  output_plugin->moveDirectory(test_directory / "unknown", test_directory / "new_unknown"); //throw OutputPluginException
}

/* ------------------------------------------------------------------------- */

