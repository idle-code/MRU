#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER

#include <data_tree/data_tree.hpp>
#include <dynamic_module.hpp>

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
  typedef data_tree::name_type name_type;
  typedef std::string path_type;

  typedef bool (*plugin_sygnature_type)(const data_tree::value_type &a_node);

  static data_tree::path_type plugin_path;
  static const data_tree::path_type module_path;
  static const data_tree::path_type entrypoint_path;

public:
  basic_plugin_manager(void);
  basic_plugin_manager(const self_type &a_other);
  ~basic_plugin_manager(void);

  const path_type& directory_prefix(void) const;
  void directory_prefix(const path_type &a_path);

  int load(const path_type &a_path);
  void unload(data_tree &a_module_node); //FIXME: protected?
  void unload_all(void);

  plugin_type* get_plugin(const name_type &a_plugin_name);
  bool register_plugin(plugin_type *a_plugin);
  void unregister_plugin(const name_type &a_plugin_name);
  void unregister_all(void);

  const data_tree& tree(void) const;

  plugin_sygnature_type entrypoint(const data_tree::path_type &a_path);
  void add_callback(const data_tree::path_type &a_path, plugin_sygnature_type a_callback);
  void set_callback(const data_tree::path_type &a_path, plugin_sygnature_type a_callback);
protected:
  data_tree m_tree;
  path_type m_plugins_directory;

  static bool empty_callback(const data_tree::value_type &a_value);
};

/* ------------------------------------------------------------------------- */

} /* namespace mru */


#define PLUGIN_MANAGER_IMPL_HPP
#include "plugin_manager_impl.hpp"
#undef PLUGIN_MANAGER_IMPL_HPP

#endif /* PLUGIN_MANAGER */

