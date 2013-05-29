#ifndef PLUGIN_MANAGER_HPP
#define PLUGIN_MANAGER_HPP

#include <string>
#include <map>
#include <list>

namespace mru
{

template<typename interface_type>
class plugin_manager {
public:
  typedef plugin_manager<interface_type> self_type;
  typedef std::string typeinfo_type; // type used to pass type information from DLL
public:
  class abstract_plugin_factory;
  template<typename implementation_type>
  class plugin_factory;

public:
  plugin_manager(void);
  ~plugin_manager(void);
  
  //void register_instance(typeinfo_type a_typeinfo, interface_type *a_instance);
  void register_factory(abstract_plugin_factory *a_factory);
  //void register_factory(typeinfo_type a_typeinfo, const plugin_factory<interface_type> &a_factory);
  
  int load_module(

  std::list<typeinfo_type> available_plugins(void) const;

  interface_type* get_instance(typeinfo_type a_typeinfo);
  void free_instance(interface_type *a_instance);
private:
  plugin_manager(const self_type &a_other); //disabled for now

  std::map<typeinfo_type, abstract_plugin_factory*> m_factories;
  std::map<interface_type*, typeinfo_type> m_plugins;
};

/* ------------------------------------------------------------------------- */

template<typename interface_type>
class plugin_manager<interface_type>::abstract_plugin_factory {
public:
  typedef abstract_plugin_factory self_type;
  typedef plugin_manager<interface_type> plugin_manager_type;
  typedef typename plugin_manager_type::typeinfo_type typeinfo_type;
public:
  abstract_plugin_factory(typeinfo_type a_typeinfo);
  virtual ~abstract_plugin_factory(void);
  const typeinfo_type& get_typeinfo(void) const;

  virtual interface_type* get_instance(void) = 0;
  virtual void free_instance(interface_type *a_instance) = 0;
private:
  const typeinfo_type m_typeinfo;
};

/* ------------------------------------------------------------------------- */

template<typename interface_type>
template<typename implementation_type>
class plugin_manager<interface_type>::plugin_factory : public plugin_manager<interface_type>::abstract_plugin_factory { //FIXME: move methods to plugin_interface_factory an inherit from it
public:
  typedef plugin_manager<interface_type>::abstract_plugin_factory parent_type;
  typedef plugin_factory<implementation_type> self_type;
  typedef typename parent_type::plugin_manager_type plugin_manager_type;
  typedef typename plugin_manager_type::typeinfo_type typeinfo_type;
public:
  plugin_factory(typeinfo_type a_typeinfo);
  virtual ~plugin_factory(void);

  implementation_type* get_instance(void);
  void free_instance(interface_type *a_instance);
};

} /* namespace mru */

#include "plugin_manager_impl.hpp"

#endif /* PLUGIN_MANAGER_HPP */

