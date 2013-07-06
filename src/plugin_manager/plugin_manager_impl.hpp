#ifndef PLUGIN_MANAGER_IMPL_HPP
#error "This is implementation file. Use plugin_manager.hpp instead"
#else

#define NDEBUG_L //disable debugging for this file
#include <debug_l.h>
#include <dynamic_module.hpp>
#include <utility>

namespace mru
{

template<typename PluginClass>
plugin<PluginClass>::plugin(const name_type &a_interface, const name_type &a_name)
  : generic_plugin_info(a_interface, a_name)
{ } 

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
plugin_factory<PluginClass>::plugin_factory(const name_type &a_interface, const name_type &a_name)
  : generic_plugin_factory(a_interface, a_name)
{ }

#ifndef PLUGIN_HOST
template<typename PluginClass>
PluginClass *
plugin_factory<PluginClass>::create(void)
{
  return new PluginClass();
}
#endif /* PLUGIN_HOST */

template<typename PluginClass>
void
plugin_factory<PluginClass>::destroy(generic_plugin_info *a_instance)
{
  if(a_instance == NULL)
    return;
  a_instance->destroy();
}

template<typename PluginClass>
void
plugin_factory<PluginClass>::destroy(PluginClass *&a_instance)
{
  destroy(static_cast<generic_plugin_info*>(a_instance));
  a_instance = NULL;
}

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
plugin_manager<PluginClass>::plugin_manager(const name_type &a_interface)
  : generic_plugin_manager(a_interface)
{
  FO("plugin_manager<PluginClass>::plugin_manager(const name_type &a_interface)");
  plugin_factory_distributor::get_instance()->register_manager(this);
}

template<typename PluginClass>
void
plugin_manager<PluginClass>::destroy(void)
{
  self_type::destroy_instance();
}

template<typename PluginClass>
plugin_manager<PluginClass>::~plugin_manager(void)
{
  plugin_factory_distributor::get_instance()->unregister_manager(this);
  typename std::map<name_type, plugin_factory_type*>::iterator i = m_factories.begin();
  while(i != m_factories.end()) {
    unregister_factory(i->first); 
    i = m_factories.begin();
  }
}

template<typename PluginClass>
int
plugin_manager<PluginClass>::load_module(const filepath_type &a_path)
{
  FO("load(const filepath_type &a_path)");
  VAL(a_path);

  dynamic_module_manager* mod_manager = dynamic_module_manager::get_instance();
  dynamic_module *module = mod_manager->load(a_path);

  VAL(module);
  if(module == NULL || !module->is_loaded()) {
    mod_manager->unload(module); 
    return 0;
  } 

  MSG("Loading 'register_plugins' symbol...");
  void *register_plugins = module->get_symbol("register_plugins");
  VAL(register_plugins);
  if(register_plugins == NULL) {
    ERR("Couldn't load 'register_plugins' symbol");
    mod_manager->unload(module); 
    return 0;
  }

  return reinterpret_cast<int (*)(plugin_factory_distributor *)>(register_plugins)(plugin_factory_distributor::get_instance()); // register_plugins(plugin_factory_distributor::m_instance);
}

template<typename PluginClass>
void
plugin_manager<PluginClass>::unload_module(dynamic_module* a_module)
{
  FO("plugin_manager<PluginClass>::unload_module(dynamic_module* a_module)")
  dynamic_module_manager* mod_manager = dynamic_module_manager::get_instance();
  mod_manager->unload(a_module);
}

template<typename PluginClass>
bool
plugin_manager<PluginClass>::register_factory(generic_plugin_factory *a_factory)
{
  if(a_factory == NULL)
    return false;
  if(m_factories.find(a_factory->implementation_name()) != m_factories.end()) {
    ERR("Factory of name \'" << a_factory->implementation_name() << "\' is already managed by plugin manager");
    return false;
  }
  m_factories.insert(std::make_pair(a_factory->implementation_name(), reinterpret_cast<plugin_factory_type*>(a_factory)));
  return true;
}

template<typename PluginClass>
void
plugin_manager<PluginClass>::unregister_factory(const name_type &a_factory_name)
{
  typename std::map<name_type, plugin_factory_type*>::iterator to_remove = m_factories.find(a_factory_name);
  if(to_remove == m_factories.end()) {
    WARN("There is no factory with name \'" << a_factory_name << "\' to remove");
    return;
  }

  to_remove->second->destroy();
  to_remove->second = NULL;
  m_factories.erase(to_remove);
}

template<typename PluginClass>
typename plugin_manager<PluginClass>::plugin_factory_type *
plugin_manager<PluginClass>::get_factory(const name_type &a_name)
{
  if(m_factories.find(a_name) != m_factories.end())
    return m_factories[a_name];
  return NULL;
}

template<typename PluginClass>
typename plugin_manager<PluginClass>::plugin_type *
plugin_manager<PluginClass>::create_plugin(const name_type &a_plugin_name)
{
  FO("plugin_manager<PluginClass>::create_plugin(const name_type &a_plugin_name)");
  VAL(a_plugin_name);
  if(m_factories.find(a_plugin_name) == m_factories.end())
    return NULL;
  else {
    return reinterpret_cast<plugin_type*>(m_factories[a_plugin_name]->create());
  }
}

template<typename PluginClass>
void
plugin_manager<PluginClass>::destroy_plugin(plugin_type *&a_instance)
{
  if(a_instance == NULL)
    return;
  VAL(m_factories.size());
  if(m_factories.find(a_instance->implementation_name()) == m_factories.end()) {
    ERR("Plugin factory of name \'" << a_instance->implementation_name() << "\' is already unregistered. Cannot remove plugin's instance");
    return;
  }
  m_factories[a_instance->implementation_name()]->destroy(a_instance);
  a_instance = NULL;
}

template<typename PluginClass>
std::list<name_type>
plugin_manager<PluginClass>::available_plugins(void) const
{
  std::list<name_type> plugin_names;
  typename std::map<name_type, plugin_factory_type*>::const_iterator ci = m_factories.begin();
  for(; ci != m_factories.end(); ++ci)
    plugin_names.push_back(ci->first);
  return plugin_names;
}

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

