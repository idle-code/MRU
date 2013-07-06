#include "BoostInputPlugin_test.hpp"
#include <cppunit/ui/text/TestRunner.h>


BoostInputPlugin_tests::BoostInputPlugin_tests(void)
{
  InputPluginManager::set_instance(new InputPluginManager("InputPlugin"));
  InputPluginManager::get_instance()->load_module("../plugins/input/BoostInputPlugin/libBoostInputPlugin.so");
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
  
}

void
BoostInputPlugin_tests::single_level(void) 
{

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

