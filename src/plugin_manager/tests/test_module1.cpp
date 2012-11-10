#include "test_module.hpp"
#include <debug_l.h>

class TestPlugin1 : public MyPlugin { 
public:
  TestPlugin1(void)
    : MyPlugin("test_plugin1")
  { }

  void say_hello(void)
  {
    FO("TestPlugin1::say_hello()");
    MSG("Hello!");
  }
};

extern "C"
{

TestPlugin1* create(void)
{
  FO("test_module1::create()");
  return new TestPlugin1();
}

void destroy(TestPlugin1 *a_plugin)
{
  FO("test_module1::destroy()");
  delete a_plugin;
}

}
