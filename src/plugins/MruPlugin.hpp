#ifndef MRUPLUGIN_HPP
#define MRUPLUGIN_HPP

#include "plugin_manager.hpp"

namespace mru
{

// forward declaration:
class MruCore;

class MruPlugin : public plugin<MruPlugin> {
public:
  class Exception;
public:
  MruPlugin(const name_type &interface, const name_type &name);
  virtual ~MruPlugin(void);
  
  virtual bool Init(MruCore *mru_core);

  virtual MruCore* getCore(void);

private:
  MruCore *core;
};

class MruPlugin::Exception : public std::exception {
public:
  Exception(const std::string &module, const UnicodeString &message);
  Exception(const std::string &module, const std::string &message);
  virtual ~Exception(void) throw();
  const char* what(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  std::string module; 
  UnicodeString message; 
};

} /* namespace mru */

#endif /* MRUPLUGIN_HPP */

