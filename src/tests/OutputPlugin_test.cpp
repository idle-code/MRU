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
OutputPlugin_tests::construction(void)
{
}

void
OutputPlugin_tests::nonexisting_source_exception(void)
{

}

