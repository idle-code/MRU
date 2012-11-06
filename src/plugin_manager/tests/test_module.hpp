#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

#include <plugin_manager.hpp>

class MyPlugin : public mru::basic_plugin<MyPlugin> {
public:
  typedef MyPlugin self_type;
public:
  MyPlugin(void);
  MyPlugin(const self_type &a_other);
  virtual ~MyPlugin(void);

  virtual void say_hello(void) = 0;
};

typedef mru::basic_plugin_manager<MyPlugin> my_plugin_manager;

#endif /* TEST_MODULE_HPP */

