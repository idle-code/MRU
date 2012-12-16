#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER

#include <data_tree/registry.hpp>
#include <dynamic_module.hpp>
#include <types.hpp>
#include <map>

namespace mru
{

template<typename PluginClass>
class basic_plugin_manager;

/* ------------------------------------------------------------------------- */

class generic_plugin_info {
public:
  generic_plugin_info(const name_type &a_type, const name_type &a_name);
  virtual void destroy(void);

  virtual const name_type& name(void) const;
  virtual const name_type& type(void) const;
protected:
  virtual ~generic_plugin_info(void);
private:
  const name_type m_name;
  const name_type m_type;
};

template<typename PluginClass>
class plugin : public generic_plugin_info { //FIXME: use generic_plugin_info instead?
public:
  plugin(const name_type &a_type, const name_type &a_name);
};

/* ------------------------------------------------------------------------- */

class generic_plugin_factory : public generic_plugin_info {
public:
  generic_plugin_factory(const name_type &a_type, const name_type &a_name);
  virtual generic_plugin_info* create(void) = 0;
  using generic_plugin_info::destroy;
  virtual void destroy(generic_plugin_info *&a_instance) = 0;
};

template<typename PluginClass> //FIXME: add PluginsType parameter to template?
class plugin_factory : public generic_plugin_factory {
public:
  plugin_factory(const name_type &a_type, const name_type &a_name);
#ifndef PLUGIN_HOST
  PluginClass* create(void);
#endif
  using generic_plugin_factory::destroy;
  void destroy(generic_plugin_info *&a_instance);
};

/* ------------------------------------------------------------------------- */

class generic_plugin_manager : public generic_plugin_info {
public:
  generic_plugin_manager(const name_type &a_type);
  virtual bool register_factory(generic_plugin_factory *a_factory) = 0;
  virtual void unregister_factory(const name_type &a_name) = 0;
};

template<typename PluginClass>
class plugin_manager : public generic_plugin_manager, public singleton1<plugin_manager<PluginClass>, const name_type &> {
public:
  typedef plugin_manager self_type;
  typedef PluginClass plugin_type;
  typedef plugin_factory<plugin_type> plugin_factory_type;
  typedef data_tree::registry registry;

public:
  plugin_manager(const name_type &a_type);
  ~plugin_manager(void);

  int load_module(const filepath_type &a_path);
  void unload_module(dynamic_module *a_module); //FIXME: replace by unload_plugin or something
  //void unload_all(void);

  bool register_factory(generic_plugin_factory *a_factory);
  void unregister_factory(const name_type &a_name);

  plugin_type* get_plugin(const name_type &a_name);

  const registry& tree(void) const;

protected:
  registry m_tree;
  std::map<name_type, plugin_factory_type*> m_factories;
};

/* ------------------------------------------------------------------------- */

class plugin_factory_distributor : public singleton<plugin_factory_distributor> {
public:
  plugin_factory_distributor(void);
  ~plugin_factory_distributor(void);

  bool register_factory(generic_plugin_factory *a_factory);
  bool register_manager(generic_plugin_manager *a_manager);
protected:
  std::map<name_type, generic_plugin_manager*> m_plugin_managers;
};

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#define PLUGIN_MANAGER_IMPL_HPP
#include "plugin_manager_impl.hpp"
#undef PLUGIN_MANAGER_IMPL_HPP

#define EXPORT_START \
  extern "C" { \
    int register_plugins(mru::plugin_factory_distributor *a_distributor) { \
      int plugins_added = 0; \
      if(a_distributor == NULL) return -1;

#define EXPORT_PLUGIN(PluginClass, PluginType) \
      plugins_added += a_distributor->register_factory(new mru::plugin_factory<PluginClass>(PluginType, #PluginClass));

#define EXPORT_END \
      return plugins_added; \
    } \
  }

#endif /* PLUGIN_MANAGER */

