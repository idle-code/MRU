#include "OutputPlugin_tests.hpp"

void
OutputPlugin_tests::copy_target_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->overrideTarget());

  createFile(test_directory / "b");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "b"));

  output_plugin->copy(test_directory / "a", test_directory / "b"); //throw OutputPluginException
}

void
OutputPlugin_tests::copy_target_exists_override(void)
{
  output_plugin->overrideTarget(true);
  CPPUNIT_ASSERT(output_plugin->overrideTarget());

  createFile(test_directory / "a");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));
  createFile(test_directory / "b");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "b"));

  output_plugin->copy(test_directory / "a", test_directory / "b");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "b"));
}

void
OutputPlugin_tests::copy_no_target_exists(void)
{
  createFile(test_directory / "a");
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "new_a"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));

  output_plugin->copy(test_directory / "a", test_directory / "new_a");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "new_a"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));
}

void
OutputPlugin_tests::copy_no_source_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "unknown"));

  output_plugin->copy(test_directory / "unknown", test_directory / "new_unknown"); //throw OutputPluginException
}

void
OutputPlugin_tests::copy_no_target_path_exists(void)
{
  createFile(test_directory / "source_file");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "source_file"));
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part"));

  output_plugin->copy(test_directory / "source_file", test_directory / "directory_part" / "new_source_file"); //throw OutputPluginException
}

void
OutputPlugin_tests::copy_no_target_path_exists_create_new(void)
{
  output_plugin->createNewPath(true);
  CPPUNIT_ASSERT(output_plugin->createNewPath());
  createFile(test_directory / "source_file");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "source_file"));
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part"));

  output_plugin->copy(test_directory / "source_file", test_directory / "directory_part" / "new_source_file");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "source_file"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "directory_part"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "directory_part" / "new_source_file"));
}

