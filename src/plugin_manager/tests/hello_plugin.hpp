#ifndef HELLO_PLUGIN_HPP
#define HELLO_PLUGIN_HPP

#include <plugin_manager.hpp>
#include <debug_l.h>

class HelloPlugin : public mru::basic_plugin<HelloPlugin> {
public:
  HelloPlugin(const std::string &a_name)
    : mru::basic_plugin<HelloPlugin>(a_name)
  {
    FO("HelloPlugin()");
  }
};

typedef mru::basic_plugin_manager<HelloPlugin> HelloPluginManager;

#endif /* HELLO_PLUGIN_HPP */

