#include "test_module.hpp"
#include <debug_l.h>

class MPlg2 : public MyPlugin { 
public:
  MPlg2(void)
    : MyPlugin("MPlg2") { } 
  void say_hello(void)
  {
    FO("void MPlg2::say_hello(void)");
    MSG("Hello from second plugin!");
  }
};

EXPORT_START
  EXPORT_PLUGIN(MPlg2, "MyPlugin")
EXPORT_END

