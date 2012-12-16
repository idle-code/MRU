#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

#include <plugin_manager.hpp>

class MyPlugin : public mru::plugin<MyPlugin> {
public:
  MyPlugin(const mru::name_type &a_name)
    : mru::plugin<MyPlugin>("MyPlugin", a_name)
  { }
  virtual void say_hello(void) = 0;
};

typedef mru::plugin_manager<MyPlugin> MyPluginManager;

class YourPlugin : public mru::plugin<YourPlugin> {
public:
  YourPlugin(const mru::name_type &a_name)
    : mru::plugin<YourPlugin>("YourPlugin", a_name)
  { }
  virtual void say_goodbye(void) = 0;
};

typedef mru::plugin_manager<YourPlugin> YourPluginManager;

#endif /* TEST_MODULE_HPP */

