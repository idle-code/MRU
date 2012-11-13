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

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
typename basic_plugin_manager<PluginClass>::data_tree::path_type
basic_plugin_manager<PluginClass>::plugin_path = ".plugin";

template<typename PluginClass>
const typename basic_plugin_manager<PluginClass>::data_tree::path_type
basic_plugin_manager<PluginClass>::module_path = ".module";

template<typename PluginClass>
const typename basic_plugin_manager<PluginClass>::data_tree::path_type
basic_plugin_manager<PluginClass>::entrypoint_path = ".entrypoint";

template<typename PluginClass>
basic_plugin_manager<PluginClass>::basic_plugin_manager(void)
{
  //FO("basic_plugin_manager<PluginClass>::basic_plugin_manager(void)");
}

template<typename PluginClass>
basic_plugin_manager<PluginClass>::basic_plugin_manager(const self_type &a_other)
{
  //FO("basic_plugin_manager<PluginClass>::basic_plugin_manager(const self_type &a_other)");
}

template<typename PluginClass>
basic_plugin_manager<PluginClass>::~basic_plugin_manager(void)
{
  unload_all();
}

template<typename PluginClass>
int
basic_plugin_manager<PluginClass>::load(const path_type &a_path)
{
  FO("load(const path_type &a_path)");
  VAL(a_path);

  dynamic_module *module = dynamic_module::load(a_path);

  VAL(module);
  if(module == NULL || !module->is_loaded()) {
    return 0;
  } 

  MSG("Loading 'create' symbol...");
  void *create_handle = module->get_symbol("create");
  VAL(create_handle);
  if(create_handle == NULL) {
    ERR("Couldn't load 'create' symbol");
    return 0;
  }

  MSG("Loading 'destroy' symbol...");
  void *destroy_handle = module->get_symbol("destroy");
  VAL(destroy_handle);
  if(destroy_handle == NULL) {
    ERR("Couldn't load 'destroy' symbol");
    return 0;
  }

  // register module:
  MSG("Registering module...");
  data_tree &mod_node =  m_tree[module_path].create_sub("", module); //create unnamed sub
  mod_node.create("create_handle", create_handle);
  mod_node.create("destroy_handle", destroy_handle);
 
  int old_size = m_tree.size(); 
  reinterpret_cast<void (*)(void)>(create_handle)(); // create();

  return m_tree.size() - old_size; 
}

template<typename PluginClass>
void
basic_plugin_manager<PluginClass>::unload(data_tree &a_module_node)
{
  FO("basic_plugin_manager<PluginClass>::unload(data_tree &a_module_node)");
  if(a_module_node.empty())
    return;
  
  //FIXME: somehow unregister plugins associated with unloaded module
  
  //FIXME: check node type
  dynamic_module *module = reinterpret_cast<dynamic_module*>(a_module_node.get().get<void*>());
  if(module == NULL) {
    ERR("Misformed module node: no dynamic_module object found");
    return;
  }

  void *destroy_handle = a_module_node.get_or("destroy_handle", static_cast<void*>(NULL));
  if(destroy_handle == NULL) {
    WARN("Warning: no 'destroy' handle found for module");
  } else {
    MSG("Calling 'destroy' function...");
    reinterpret_cast<void (*)(self_type *)>(destroy_handle)(this); // destroy(this);
  }

  delete module;
  a_module_node.clear();
  a_module_node.set(NULL);
}

template<typename PluginClass>
void
basic_plugin_manager<PluginClass>::unload_all(void)
{
  FO("basic_plugin_manager<PluginClass>::unload_all(void)");
  //unregister_all();
  data_tree::node_iterator ni = m_tree[module_path].begin();
  data_tree::node_iterator ni_end = m_tree[module_path].end();
  for(; ni != ni_end; ++ni) {
    unload(*ni);
  }
  m_tree[module_path].clear();
}


template<typename PluginClass>
typename basic_plugin_manager<PluginClass>::plugin_type *
basic_plugin_manager<PluginClass>::get_plugin(const name_type &a_plugin_name)
{
  //FO("basic_plugin_manager<PluginClass>::get_plugin(const name_type &a_plugin_name)");
  //VAL(a_plugin_name);
  if(!m_tree.exists(plugin_path / a_plugin_name))
    return NULL;
  return reinterpret_cast<plugin_type*>(m_tree.get(plugin_path / a_plugin_name).template get<void*>());
}

template<typename PluginClass>
bool
basic_plugin_manager<PluginClass>::register_plugin(plugin_type *a_plugin)
{
  FO("basic_plugin_manager<PluginClass>::register_plugin(plugin_type *a_plugin)");
  if(a_plugin == NULL)
    return false;
  VAL(a_plugin);
  if(m_tree.exists(plugin_path / a_plugin->name())) {
    ERR("Plugin named '" << plugin_path / a_plugin->name() << "' already exists");
    return false;
  }
  MSG("Adding plugin: " << std::string(plugin_path / a_plugin->name()));
  m_tree[plugin_path].create_sub(a_plugin->name(), static_cast<void*>(a_plugin)); // create ".plugins.<plugin_name>" branch
  //m_tree.set(plugin_path / a_plugin->name(), static_cast<void*>(a_plugin)); // create ".plugins.<plugin_name>" branch

  return true;
}

template<typename PluginClass>
void
basic_plugin_manager<PluginClass>::unregister_plugin(const name_type &a_plugin_name)
{
  FO("basic_plugin_manager<PluginClass>::unregister_plugin(const name_type &a_plugin_name)");
  VAL(a_plugin_name);
  if(!m_tree.exists(plugin_path / a_plugin_name)) {
    WARN("Plugin '" << a_plugin_name << "' not loaded");
    return;
  }

  MSG("Removing plugin's node: " << std::string(plugin_path / a_plugin_name));
  m_tree.remove(plugin_path / a_plugin_name);
}

template<typename PluginClass>
void
basic_plugin_manager<PluginClass>::unregister_all(void)
{
  FO("basic_plugin_manager<PluginClass>::unregister_all(void)");
  data_tree::node_iterator ni = m_tree[plugin_path].begin();
  data_tree::node_iterator ni_end = m_tree[plugin_path].end();
  for(; ni != ni_end; ++ni) {
    unregister_plugin(ni.name());
  }
  m_tree[plugin_path].clear();
}

template<typename PluginClass>
const typename basic_plugin_manager<PluginClass>::data_tree &
basic_plugin_manager<PluginClass>::tree(void) const
{
  return m_tree;
}


} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

