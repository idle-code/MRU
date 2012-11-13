#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

#include <plugin_manager.hpp>

class MyPlugin : public mru::basic_plugin<MyPlugin> {
public:
  typedef MyPlugin self_type;
public:
  MyPlugin(const name_type &a_name)
    : mru::basic_plugin<MyPlugin>(a_name)
  { }
  virtual void say_hello(void) = 0;
};

typedef mru::basic_plugin_manager<MyPlugin> MyPluginManager;

#endif /* TEST_MODULE_HPP */

