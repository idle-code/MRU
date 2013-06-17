#ifndef MRUPLUGIN_HPP
#define MRUPLUGIN_HPP

#include "plugin_manager.hpp"

namespace mru
{

// forward declaration:
class MruCore;

class MruPlugin : public plugin<MruPlugin> {
public:
  typedef MruPlugin self_type;
public:
  MruPlugin(const name_type &a_interface, const name_type &a_name);
  virtual ~MruPlugin(void);
  
  virtual bool Init(MruCore *a_mru_core);

  virtual MruCore* core(void);
  virtual registry reg(void);

protected:
  MruCore *m_core;
};

} /* namespace mru */

#endif /* MRUPLUGIN_HPP */

