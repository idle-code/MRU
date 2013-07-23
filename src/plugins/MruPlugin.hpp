#ifndef MRUPLUGIN_HPP
#define MRUPLUGIN_HPP

#include "plugin_manager.hpp"

namespace mru
{

class MruPluginException : public std::exception {
public:
  MruPluginException(const std::string &module, const UnicodeString &message);
  MruPluginException(const std::string &module, const std::string &message);
  virtual ~MruPluginException(void) throw();
  const char* what(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  std::string module; 
  UnicodeString message; 
};

/* ------------------------------------------------------------------------- */

// forward declaration:
class MruCore;

class MruPlugin : public plugin<MruPlugin> {
public:
  MruPlugin(const name_type &interface, const name_type &name);
  virtual ~MruPlugin(void);
  
  virtual bool Init(MruCore *mru_core);

  virtual MruCore* getCore(void);

private:
  MruCore *core;
};

} /* namespace mru */

#endif /* MRUPLUGIN_HPP */

