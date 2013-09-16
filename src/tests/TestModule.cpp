#include "TestModule.hpp"

extern "C" {

int
hello(void)
{
  return 321;
}

}

/* ------------------------------------------------------------------------- */

extern "C" {

void
registerITestPluginFactory(ITestPlugin::Manager *plugin_manager)
{
  assert(plugin_manager);
  plugin_manager->registerFactory(MorningTestPlugin::Factory::allocateFactory("MorningTestPlugin"), &MorningTestPlugin::Factory::destroyFactory);
  plugin_manager->registerFactory(EveningTestPlugin::Factory::allocateFactory("EveningTestPlugin"), &EveningTestPlugin::Factory::destroyFactory);
}

}

