#include "OutputPlugin_tests.hpp"

void
OutputPlugin_tests::link_target_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->overrideTarget());

  createFile(test_directory / "b");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "b"));

  output_plugin->link(test_directory / "a", test_directory / "b"); //throw OutputPluginException
}

void
OutputPlugin_tests::link_target_exists_override(void)
{
  output_plugin->overrideTarget(true);
  CPPUNIT_ASSERT(output_plugin->overrideTarget());

  createFile(test_directory / "a");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));
  createFile(test_directory / "b");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "b"));

  output_plugin->link(test_directory / "a", test_directory / "b");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "b"));
  CPPUNIT_ASSERT_EQUAL(test_directory / "a", output_plugin->resolveLink(test_directory / "b"));
}

void
OutputPlugin_tests::link_no_target_exists(void)
{
  createFile(test_directory / "a");
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "new_a"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));

  output_plugin->link(test_directory / "a", test_directory / "new_a");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "new_a"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "a"));
  CPPUNIT_ASSERT_EQUAL(test_directory / "a", output_plugin->resolveLink(test_directory / "new_a"));
}

void
OutputPlugin_tests::link_no_source_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "unknown"));

  output_plugin->link(test_directory / "unknown", test_directory / "new_unknown"); //throw OutputPluginException
}

void
OutputPlugin_tests::link_no_target_path_exists(void)
{
  createFile(test_directory / "source_file");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "source_file"));
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part"));

  output_plugin->link(test_directory / "source_file", test_directory / "directory_part" / "new_source_file"); //throw OutputPluginException
}

void
OutputPlugin_tests::link_no_target_path_exists_create_new(void)
{
  output_plugin->createNewPath(true);
  CPPUNIT_ASSERT(output_plugin->createNewPath());
  createFile(test_directory / "source_file");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "source_file"));
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "directory_part"));

  output_plugin->link(test_directory / "source_file", test_directory / "directory_part" / "new_source_file");

  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "source_file"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "directory_part"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "directory_part" / "new_source_file"));
  CPPUNIT_ASSERT_EQUAL(test_directory / "source_file", output_plugin->resolveLink(test_directory / "directory_part" / "new_source_file"));
}

void
OutputPlugin_tests::resolveLink_target_exists(void)
{
  createFile(test_directory / "test_target");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "test_target"));
  output_plugin->link(test_directory / "test_target", test_directory / "test_link");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "test_target"));
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "test_link"));
  
  CPPUNIT_ASSERT_EQUAL(test_directory / "test_target", output_plugin->resolveLink(test_directory / "test_link"));
}

void
OutputPlugin_tests::resolveLink_not_link_target_exists(void)
{
  createFile(test_directory / "test_link");
  CPPUNIT_ASSERT(output_plugin->exists(test_directory / "test_link"));
  
  output_plugin->resolveLink(test_directory / "test_link"); //throw OutputPluginException
}

void
OutputPlugin_tests::resolveLink_no_target_exists(void)
{
  CPPUNIT_ASSERT(!output_plugin->exists(test_directory / "test_link"));
  
  output_plugin->resolveLink(test_directory / "test_link"); //throw OutputPluginException
}


