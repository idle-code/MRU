#ifndef PLUGIN_MANAGER_IMPL_HPP
#error "This is implementation file. Use plugin_manager.hpp instead"
#else

#include <debug_l.h>
#include <dynamic_module.hpp>

namespace mru
{

template<typename PluginClass>
basic_plugin<PluginClass>::basic_plugin(const name_type &a_name)
  : m_name(a_name)
{ }

template<typename PluginClass>
basic_plugin<PluginClass>::~basic_plugin(void)
{

}

template<typename PluginClass>
const typename basic_plugin<PluginClass>::name_type &
basic_plugin<PluginClass>::name(void) const
{
  return m_name;
}

template<typename PluginClass>
bool
basic_plugin<PluginClass>::register_plugin(data_tree &a_tree)
{
  FO("basic_plugin<PluginClass>::register_plugin(data_tree &a_tree)");


  return true;
}

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
basic_plugin_manager<PluginClass>::basic_plugin_manager(void)
  : m_tree_prefix(".plugins")
{
  FO("basic_plugin_manager<PluginClass>::basic_plugin_manager(void)");
  m_tree.add_sub(m_tree_prefix);
}

template<typename PluginClass>
basic_plugin_manager<PluginClass>::basic_plugin_manager(const self_type &a_other)
  : m_tree_prefix(".plugins")
{
  FO("basic_plugin_manager<PluginClass>::basic_plugin_manager(const self_type &a_other)");
  m_tree.add_sub(m_tree_prefix);
}

template<typename PluginClass>
basic_plugin_manager<PluginClass>::~basic_plugin_manager(void)
{

}

template<typename PluginClass>
typename basic_plugin_manager<PluginClass>::plugin_type*
basic_plugin_manager<PluginClass>::load(const path_type &a_path)
{
  FO("load(const path_type &a_path)");
  VAL(a_path);

  dynamic_module *module = dynamic_module::load(a_path);

  VAL(module);
  if(module == NULL) {
    return NULL;
  } 

  MSG("Loading 'create' symbol...");
  void *create_handle = module->get_symbol("create");
  VAL(create_handle);
  if(create_handle == NULL) {
    ERR("Couldn't load 'create' symbol");
    return NULL;
  }

  MSG("Loading 'destroy' symbol...");
  void *destroy_handle = module->get_symbol("destroy");
  VAL(destroy_handle);
  if(destroy_handle == NULL) {
    ERR("Couldn't load 'destroy' symbol");
    return NULL;
  }
  
  plugin_type* plugin = reinterpret_cast<plugin_type* (*)(void)>(create_handle)(); // plugin = create();
  typename data_tree::path_type plugin_path = m_tree_prefix / plugin->name();
  if(m_tree.exists(plugin_path)) {
    ERR("Plugin named '" << static_cast<data_tree::path_type::value_type>(plugin_path) << "' already exists");
    return NULL;
  }
  MSG("adding plugin: " << std::string(plugin_path));
  m_tree.add_sub(plugin_path);
  m_tree.add_sub(plugin_path/"create", static_cast<void*>(create_handle));
  m_tree.add_sub(plugin_path/"destroy", static_cast<void*>(destroy_handle));
  m_tree.add_sub(plugin_path/"stroy", static_cast<void*>(destroy_handle));

  if(!plugin->register_plugin(m_tree)) {
    ERR("Error while registering plugin");
    return NULL;
  }

  return plugin; 
}

template<typename PluginClass>
void
basic_plugin_manager<PluginClass>::unload(plugin_type *a_plugin)
{
  FO("basic_plugin_manager<PluginClass>::unload(plugin_type *a_plugin)");
  if(a_plugin == NULL)
    return;
  data_tree::path_type plugin_path = m_tree_prefix / a_plugin->name();
  if(!m_tree.exists(plugin_path)) {
    WARN("Plugin '" << a_plugin->name() << "' not loaded");
    return;
  }
  //void *destroy_handle = m_tree(plugin_path, static_cast<void*>(NULL)).get<void*>();
  void *destroy_handle = NULL; //m_tree(plugin_path, static_cast<void*>(NULL));
  if(destroy_handle == NULL) {
    WARN("Warning: no 'destroy' handle found for plugin '" << a_plugin->name() << "'");
  }
  reinterpret_cast<void (*)(plugin_type *)>(destroy_handle)(a_plugin);
  m_tree.remove_sub(plugin_path);
}

template<typename PluginClass>
const typename basic_plugin_manager<PluginClass>::data_tree &
basic_plugin_manager<PluginClass>::tree(void) const
{
  return m_tree;
}


} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

