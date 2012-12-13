#include "hello_plugin.hpp"

class FirstHelloPlugin : public HelloPlugin {
public:
  FirstHelloPlugin() : HelloPlugin("FirstHelloPlugin")
  {
    FO("FirstHelloPlugin()");
  }
};


extern "C"
{

void
create(HelloPluginManager *a_hpm)
{
  a_hpm->register_plugin(new FirstHelloPlugin());
}

void
destroy(HelloPluginManager *a_hpm)
{

}

}
