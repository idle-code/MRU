#ifndef PLUGIN_MANAGER_IMPL_HPP
#error "This is implementation file. Use plugin_manager.hpp instead"
#else

#include <debug_l.h>
#include <dynamic_module.hpp>
#include <utility>

namespace mru
{

/* ------------------------------------------------------------------------- */

generic_plugin_info::generic_plugin_info(const name_type &a_type, const name_type &a_name)
  : m_type(a_type), m_name(a_name)
{ }

generic_plugin_info::~generic_plugin_info(void)
{ }

const name_type &
generic_plugin_info::name(void) const
{
  return m_name;
}

const name_type &
generic_plugin_info::type(void) const
{
  return m_type;
}

void
generic_plugin_info::destroy(void)
{
  this->~generic_plugin_info();
  delete this;
}

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
plugin<PluginClass>::plugin(const name_type &a_type, const name_type &a_name)
  : generic_plugin_info(a_type, a_name)
{ } 

/* ------------------------------------------------------------------------- */

generic_plugin_factory::generic_plugin_factory(const name_type &a_type, const name_type &a_name)
  : generic_plugin_info(a_type, a_name)
{ }

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
plugin_factory<PluginClass>::plugin_factory(const name_type &a_type, const name_type &a_name)
  : generic_plugin_factory(a_type, a_name)
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
plugin_factory<PluginClass>::destroy(generic_plugin_info *&a_instance)
{
  if(a_instance == NULL)
    return;
  a_instance->destroy();
  a_instance = NULL;
}

/* ------------------------------------------------------------------------- */

generic_plugin_manager::generic_plugin_manager(const name_type &a_type)
  : generic_plugin_info(a_type, a_type + "_manager")
{ }

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
plugin_manager<PluginClass>::plugin_manager(const name_type &a_type)
  : generic_plugin_manager(a_type)
{
  FO("plugin_manager<PluginClass>::plugin_manager(void)");
  plugin_factory_distributor::get_instance()->register_manager(this);
}

//template<typename PluginClass>
//plugin_manager<PluginClass>::plugin_manager(const self_type &a_other)
//{
//  //FO("plugin_manager<PluginClass>::plugin_manager(const self_type &a_other)");
//}

template<typename PluginClass>
plugin_manager<PluginClass>::~plugin_manager(void)
{
  //unload_all();
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
  //FO("plugin_manager<PluginClass>::unload(registry &a_module_node)");
  dynamic_module_manager* mod_manager = dynamic_module_manager::get_instance();
  mod_manager->unload(a_module);
}

template<typename PluginClass>
bool
plugin_manager<PluginClass>::register_factory(generic_plugin_factory *a_factory)
{
  if(a_factory == NULL)
    return false;
  if(m_factories.find(a_factory->name()) != m_factories.end()) {
    ERR("Factory of name \'" << a_factory->name() << "\' is already managed by plugin manager");
    return false;
  }
  m_factories.insert(std::make_pair(a_factory->name(), reinterpret_cast<plugin_factory_type*>(a_factory)));
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
  (*to_remove).second->destroy();
  (*to_remove).second = NULL;
  m_factories.erase(to_remove);
}

template<typename PluginClass>
typename plugin_manager<PluginClass>::plugin_type *
plugin_manager<PluginClass>::get_plugin(const name_type &a_plugin_name)
{
  FO("plugin_manager<PluginClass>::get_plugin(const name_type &a_plugin_name)");
  VAL(a_plugin_name);
  if(m_factories.find(a_plugin_name) == m_factories.end())
    return NULL;
  else {
    return reinterpret_cast<plugin_type*>(m_factories[a_plugin_name]->create());
  }
}

template<typename PluginClass>
const typename plugin_manager<PluginClass>::registry &
plugin_manager<PluginClass>::tree(void) const
{
  return m_tree;
}

/* ------------------------------------------------------------------------- */

plugin_factory_distributor::plugin_factory_distributor(void)
{ }

plugin_factory_distributor::~plugin_factory_distributor(void)
{ }

bool
plugin_factory_distributor::register_factory(generic_plugin_factory *a_factory)
{
  FO("bool plugin_factory_distributor::register_factory(generic_plugin_factory *a_factory)");
  if(a_factory == NULL)
    return false;
  
  VAL(a_factory->name());
  if(m_plugin_managers.find(a_factory->type()) == m_plugin_managers.end()) {
    WARN("Unknown type of plugin factory: " << a_factory->type());
    a_factory->destroy();
    return false;
  }

  VAL(a_factory->type());
  VAL(m_plugin_managers[a_factory->type()]);
  m_plugin_managers[a_factory->type()]->register_factory(a_factory);

  return true;
}

bool
plugin_factory_distributor::register_manager(generic_plugin_manager *a_manager)
{
  FO("bool plugin_factory_distributor::register_manager(generic_plugin_manager *a_manager)");
  if(a_manager == NULL)
    return false;
  
  VAL(a_manager->type());
  if(m_plugin_managers.find(a_manager->type()) != m_plugin_managers.end()) {
    ERR("Manager with type \'" << a_manager->type() << "\' is already in registered");
    return false;
  }

  m_plugin_managers.insert(std::make_pair(a_manager->type(), a_manager));

  return true;
}

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

