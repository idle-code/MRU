#ifndef MRUPLUGIN_HPP
#define MRUPLUGIN_HPP

#include "plugin_manager.hpp"

namespace mru
{

class MruPluginException : public std::exception {
public:
  MruPluginException(const std::string &a_module, const UnicodeString &a_message);
  MruPluginException(const std::string &a_module, const std::string &a_message);
  virtual ~MruPluginException(void) throw();
  const char* what(void) const throw();
  const UnicodeString& message(void) const throw();
private:
  std::string m_module; 
  UnicodeString m_message; 
};

/* ------------------------------------------------------------------------- */

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

private:
  MruCore *m_core;
};

} /* namespace mru */

#endif /* MRUPLUGIN_HPP */

