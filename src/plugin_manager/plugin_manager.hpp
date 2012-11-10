#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER

#include <data_tree/data_tree.hpp>

namespace mru
{
template<typename PluginClass>
class basic_plugin_manager;

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
class basic_plugin {
public:
  typedef PluginClass self_type;
  typedef typename basic_plugin_manager<PluginClass>::data_tree data_tree;
  typedef basic_plugin_manager<PluginClass> plugin_manager_type;
  typedef typename data_tree::name_type name_type;
public:
  basic_plugin(const name_type &a_plugin_name);
  virtual ~basic_plugin(void);

  const name_type& name(void) const;
  virtual bool register_plugin(data_tree &a_tree);

protected:
  name_type m_name;
};

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
class basic_plugin_manager {
public:
  typedef basic_plugin_manager self_type;
  typedef PluginClass plugin_type;
  typedef data_tree::data_tree data_tree;
  //typedef data_tree::name_type path_type;
  typedef std::string path_type;
public:
  basic_plugin_manager(void);
  basic_plugin_manager(const self_type &a_other);
  ~basic_plugin_manager(void);

  plugin_type* load(const path_type &a_path);
  void unload(plugin_type *a_plugin);

  const data_tree& tree(void) const;
protected:
  typename data_tree::path_type m_plugins_prefix;
  data_tree m_tree;
};

/* ------------------------------------------------------------------------- */

} /* namespace mru */


#define PLUGIN_MANAGER_IMPL_HPP
#include "plugin_manager_impl.hpp"
#undef PLUGIN_MANAGER_IMPL_HPP

#endif /* PLUGIN_MANAGER */

