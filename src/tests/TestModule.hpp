#ifndef TEST_PLUGIN_HPP
#define TEST_PLUGIN_HPP

#include "../PluginManager.hpp"
#include <boost/shared_ptr.hpp>
#include <string>

class ITestPlugin {
public:
  static const char* getRegisterFunctionName(void) { return "registerITestPluginFactory"; }
  typedef boost::shared_ptr<ITestPlugin> Pointer;
  typedef mru::PluginManager<ITestPlugin> Manager;

  virtual ~ITestPlugin(void) { }
  virtual std::string sayHello(void) = 0;
};

/* ------------------------------------------------------------------------- */

class MorningTestPlugin : public ITestPlugin {
public:
  typedef mru::PluginFactory<MorningTestPlugin, ITestPlugin> Factory;
  MorningTestPlugin(void) { }

  std::string
  sayHello(void) {
    return "Morning!";
  }
};

class EveningTestPlugin : public ITestPlugin {
public:
  typedef mru::PluginFactory<EveningTestPlugin, ITestPlugin> Factory;
  EveningTestPlugin(void) { }

  std::string
  sayHello(void) {
    return "Good evening!";
  }
};

#endif /* TEST_PLUGIN_HPP */

