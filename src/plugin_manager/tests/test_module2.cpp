#include "test_module.hpp"
#include <debug_l.h>

class OtherTestPlugin : public MyPlugin { 
public:
  OtherTestPlugin(void)
    : MyPlugin("OtherTestPlugin")
  { }

  void say_hello(void)
  {
    FO("OtherTestPlugin::say_hello()");
    MSG("Hello!");
  }
};

extern "C"
{

void
create(MyPluginManager *a_manager)
{
  FO("create(MyPluginManager *a_manager)");
  MyPlugin *test_plugin_1 = new OtherTestPlugin();
  a_manager->register_plugin(test_plugin_1);
}

void
destroy(MyPluginManager *a_manager)
{
  FO("destroy(MyPluginManager *a_manager)");
  MyPlugin* test_plugin_1 = a_manager->get_plugin("OtherTestPlugin");
  a_manager->unregister_plugin("OtherTestPlugin1");
  delete test_plugin_1;
}

}
