#ifndef DYNAMIC_PLUGIN_MANAGER_HPP
#define DYNAMIC_PLUGIN_MANAGER_HPP

#include "PluginManager.hpp"
#include "DllModule.hpp"

namespace mru {

template<typename PluginInterface, typename IdType=std::string>
class DynamicPluginManager : public PluginManager<PluginInterface, IdType> {
public:
  typedef DynamicPluginManager Self;
  typedef PluginManager<PluginInterface, IdType> Parent;
  MODULE_EXCEPTION(DynamicPluginManager, Parent::Exception);
public:
  DynamicPluginManager(void);

  void registerModule(const FilePath &module_path);
  
private:
  std::list<DllModule::Pointer> loaded_modules;
};

} /* namespace mru */

#define DYNAMIC_PLUGIN_MANAGER_IMPL_HPP
#include "DynamicPluginManager_impl.hpp"
#undef DYNAMIC_PLUGIN_MANAGER_IMPL_HPP

#endif /* DYNAMIC_PLUGIN_MANAGER_HPP */

