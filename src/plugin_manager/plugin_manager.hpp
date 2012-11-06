#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER

#include <string>

namespace mru
{

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
class basic_plugin {
public:
  typedef basic_plugin self_type;
public:
  basic_plugin(void);
  basic_plugin(const self_type &a_other);
  virtual ~basic_plugin(void) = 0;

protected:
  /* data */
};

/* ------------------------------------------------------------------------- */

template<typename PluginClass>
class basic_plugin_manager {
public:
  typedef basic_plugin_manager self_type;
  typedef PluginClass plugin_type;
  typedef std::string path_type;
public:
  basic_plugin_manager(void);
  basic_plugin_manager(const self_type &a_other);
  ~basic_plugin_manager(void);

  plugin_type* load(const path_type &a_path);
  void unload(plugin_type *a_plugin);
protected:
  /* data */
};

/* ------------------------------------------------------------------------- */

} /* namespace mru */


#define PLUGIN_MANAGER_IMPL_HPP
#include "plugin_manager_impl.hpp"
#undef PLUGIN_MANAGER_IMPL_HPP

#endif /* PLUGIN_MANAGER */

