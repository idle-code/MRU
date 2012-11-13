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

class TestPlugin2 : public MyPlugin { 
public:
  TestPlugin2(void)
    : MyPlugin("TestPlugin2")
  { }

  void say_hello(void)
  {
    FO("TestPlugin2::say_hello()");
    MSG("Hello from second plugin!");
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
  MyPlugin *test_plugin_2 = new TestPlugin2();
  a_manager->register_plugin(test_plugin_2);
}

void
destroy(MyPluginManager *a_manager)
{
  FO("destroy(MyPluginManager *a_manager)");
  MyPlugin* test_plugin_1 = a_manager->get_plugin("TestPlugin1");
  a_manager->unregister_plugin("TestPlugin1");
  delete test_plugin_1;

  MyPlugin* test_plugin_2 = a_manager->get_plugin("TestPlugin2");
  a_manager->unregister_plugin("TestPlugin2");
  delete test_plugin_2;
}

}
