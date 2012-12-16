#include "test_module.hpp"
#include <debug_l.h>

class MPlg1 : public MyPlugin { 
public:
  PLUGIN_NAME("MPlg1");
  MPlg1(void)
    : MyPlugin(static_implementation_name()) { } 

  void say_hello(void)
  {
    FO("void MPlg1::say_hello(void)");
    MSG("Hello!");
  }
};

class YPlg : public YourPlugin { 
public:
  PLUGIN_NAME("YPlg");
  YPlg(void)
    : YourPlugin(static_implementation_name()) { }

  void say_goodbye(void)
  {
    FO("void Yplg::say_goodbye(void)");
    MSG("Goodbye from YPlg plugin!");
    VAL(++counter);
  }
  static int counter;
};

int
YPlg::counter = 0;

EXPORT_START
  EXPORT_PLUGIN(MPlg1)
  EXPORT_PLUGIN(YPlg)
EXPORT_END

