#ifndef DYNAMIC_PLUGIN_MANAGER_HPP
#define DYNAMIC_PLUGIN_MANAGER_HPP

#include "PluginManager.hpp"
#include "DllModule.hpp"
#include <map>

namespace mru {

template<typename PluginInterface, typename IdType=std::string>
class DynamicPluginManager : public PluginManager<PluginInterface, IdType> {
public:
  typedef DynamicPluginManager Self;
  typedef boost::shared_ptr<Self> Pointer;
  typedef PluginManager<PluginInterface, IdType> Parent;
  MODULE_EXCEPTION(DynamicPluginManager, Parent::Exception);
  static Pointer create(void);
public:
  DynamicPluginManager(void);
  ~DynamicPluginManager(void);

  DllModule::Pointer loadModule(const FilePath &module_path);
  
private:
  std::map<FilePath, DllModule::Pointer> loaded_modules;
};

} /* namespace mru */

#define DYNAMIC_PLUGIN_MANAGER_IMPL_HPP
#include "DynamicPluginManager_impl.hpp"
#undef DYNAMIC_PLUGIN_MANAGER_IMPL_HPP

#endif /* DYNAMIC_PLUGIN_MANAGER_HPP */

