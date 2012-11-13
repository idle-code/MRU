#include "test_module.hpp"
#include <debug_l.h>

class TestPlugin1 : public MyPlugin { 
public:
  TestPlugin1(void)
    : MyPlugin("TestPlugin1")
  { }

  void say_hello(void)
  {
    FO("TestPlugin1::say_hello()");
    MSG("Hello!");
  }
};

extern "C"
{

void
create(MyPluginManager *a_manager)
{
  FO("create(MyPluginManager *a_manager)");
  MyPlugin *test_plugin_1 = new TestPlugin1();
  a_manager->register_plugin(test_plugin_1);
  data_tree::print_tree(a_manager->tree());
  VAL(test_plugin_1);
  VAL(a_manager->get_plugin(test_plugin_1->name()));
}

void
destroy(MyPluginManager *a_manager)
{
  FO("destroy(MyPluginManager *a_manager)");
  MyPlugin* test_plugin_1 = a_manager->get_plugin("TestPlugin1");
  a_manager->unregister_plugin("TestPlugin1");
  delete test_plugin_1;
}

}
