#ifndef DYNAMIC_MODULE_HPP
#define DYNAMIC_MODULE_HPP

#include <string>
#include <map>
#include "types.hpp"
#include "patterns.hpp"

namespace mru
{

class dynamic_module_manager;

class dynamic_module {
public:
  friend class dynamic_module_manager;

public:
  virtual bool load(const filepath_type &a_file_path) = 0;
  virtual bool unload(void) = 0;
  virtual bool is_loaded(void) const = 0;
  virtual void* get_symbol(const name_type &a_symbol) = 0;

  const filepath_type&        filepath(void) const;
  virtual const filename_type filename_prefix(void) const;
  virtual const filename_type filename_postfix(void) const;
protected:
  dynamic_module(void);
  virtual ~dynamic_module(void);

  filepath_type m_file_path;  
};

class dynamic_module_manager : public singleton<dynamic_module_manager> {
public:
  typedef dynamic_module_manager self_type;
  friend class singleton<dynamic_module_manager>; 
public:
  dynamic_module* load(const filepath_type &a_file_path);
  void unload(dynamic_module *&a_module);
  void unload_all(void);

protected:
  dynamic_module_manager(void);
  ~dynamic_module_manager(void);

  std::map<name_type, dynamic_module*> m_loaded_modules;
};

} /* namespace mru */

#endif /* DYNAMIC_MODULE_HPP */

