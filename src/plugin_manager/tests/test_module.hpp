#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

#include <plugin_manager.hpp>
#undef NDEBUG_L
#include <debug_l.h>

class MyPlugin : public mru::plugin<MyPlugin> {
public:
  PLUGIN_INTERFACE("MyPlugin")
  MyPlugin(const mru::name_type &a_name)
    : mru::plugin<MyPlugin>(static_interface_name(), a_name)
  { }
  virtual void say_hello(void) = 0;
};

typedef mru::plugin_manager<MyPlugin> MyPluginManager;

class YourPlugin : public mru::plugin<YourPlugin> {
public:
  PLUGIN_INTERFACE("YourPlugin")
  YourPlugin(const mru::name_type &a_name)
    : mru::plugin<YourPlugin>(static_interface_name(), a_name)
  { }
  virtual void say_goodbye(void) = 0;
};

typedef mru::plugin_manager<YourPlugin> YourPluginManager;

#endif /* TEST_MODULE_HPP */

