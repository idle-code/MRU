#ifndef TEST_PLUGIN_HPP
#define TEST_PLUGIN_HPP

#include <boost/shared_ptr.hpp>
#include <string>

class ITestPlugin {
public:
  typedef boost::shared_ptr<ITestPlugin> Pointer;

  virtual std::string sayHello(void) = 0;
};

#endif /* TEST_PLUGIN_HPP */

