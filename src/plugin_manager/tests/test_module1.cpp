#include "test_module.hpp"
#include <debug_l.h>

class MPlg1 : public MyPlugin { 
public:
  MPlg1(void)
    : MyPlugin("MPlg1") { } 

  void say_hello(void)
  {
    FO("void MPlg1::say_hello(void)");
    MSG("Hello!");
  }
};

class YPlg : public YourPlugin { 
public:
  YPlg(void)
    : YourPlugin("YPlg") { }

  void say_goodbye(void)
  {
    FO("void Yplg::say_goodbye(void)");
    MSG("Goodbye from YPlg plugin!");
  }
};

EXPORT_START
  EXPORT_PLUGIN(MPlg1, "MyPlugin")
  EXPORT_PLUGIN(YPlg, "YourPlugin")
EXPORT_END

