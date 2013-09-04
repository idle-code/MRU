#ifndef MRUPLUGIN_HPP
#define MRUPLUGIN_HPP

#include "PluginManager.hpp"
#include <cassert>

namespace mru {

// forward declaration:
class MruCore;

class MruPlugin {
public:
  MODULE_EXCEPTION(MruPlugin, MruException);
public:
  MruPlugin(void);
  virtual ~MruPlugin(void);
  
  virtual bool Init(MruCore *mru_core);

  virtual MruCore* getCore(void);

private:
  MruCore *core;
};

} /* namespace mru */


#endif /* MRUPLUGIN_HPP */

