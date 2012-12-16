#include "test_module.hpp"
#include <debug_l.h>

class MPlg2 : public MyPlugin { 
public:
  PLUGIN_NAME("MPlg2")
  MPlg2(void)
    : MyPlugin(static_implementation_name()) { } 
  void say_hello(void)
  {
    FO("void MPlg2::say_hello(void)");
    MSG("Hello from second plugin!");
  }
};

EXPORT_START
  EXPORT_PLUGIN(MPlg2)
EXPORT_END

