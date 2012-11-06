#ifndef PLUGIN_MANAGER_IMPL_HPP
#error "This is implementation file. Use plugin_manager.hpp instead"
#else
#include <debug_l.h>

namespace mru
{

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
basic_plugin_manager<PluginClass>::basic_plugin_manager(void)
{
  FO("basic_plugin_manager<PluginClass>::basic_plugin_manager(void)");
}

template<typename PluginClass>
basic_plugin_manager<PluginClass>::basic_plugin_manager(const self_type &a_other)
{

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

  return NULL;
}

template<typename PluginClass>
void
basic_plugin_manager<PluginClass>::unload(plugin_type *a_plugin)
{

}

} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

