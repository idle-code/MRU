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

bool
my_other_callback(const MyPluginManager::data_tree::value_type &a_value)
{
  FO("my_other_callback(const data_tree::value_type &a_value)");
  MSG("Some code will work here...");
  VAL(a_value.get<std::string>());
  return true;
}

void
create(MyPluginManager *a_manager)
{
  FO("create(MyPluginManager *a_manager)");
  MyPlugin *test_plugin_1 = new OtherTestPlugin();
  a_manager->register_plugin(test_plugin_1);

  a_manager->set_callback("main.before_exit", my_other_callback);
}

void
destroy(MyPluginManager *a_manager)
{
  FO("destroy(MyPluginManager *a_manager)");
  MyPlugin* test_plugin_1 = a_manager->get_plugin("OtherTestPlugin");
  a_manager->unregister_plugin("OtherTestPlugin");
  delete test_plugin_1;
}

}
