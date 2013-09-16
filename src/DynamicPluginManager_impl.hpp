#ifndef DYNAMIC_PLUGIN_MANAGER_IMPL_HPP
#  error "This is implementation file. Use DynamicPluginManager.hpp instead."
#else

#include "BsdDllModule.hpp"

namespace mru {

template<typename PluginInterface, typename IdType>
DynamicPluginManager<PluginInterface, IdType>::DynamicPluginManager(void)
{

}

template<typename PluginInterface, typename IdType>
DynamicPluginManager<PluginInterface, IdType>::~DynamicPluginManager(void)
{
  Parent::factory_map.clear();
}

template<typename PluginInterface, typename IdType>
typename DllModule::Pointer
DynamicPluginManager<PluginInterface, IdType>::loadModule(const FilePath &module_path)
{
  if (loaded_modules.count(module_path) > 0)
    return loaded_modules[module_path];

  typename DllModule::Pointer dll_module = BsdDllModule::create();
  dll_module->load(module_path);
  if (!dll_module->isLoaded())
    return DllModule::Pointer();

  typedef void (*RegisterFunction)(Parent *);
  RegisterFunction register_function = dll_module->get<RegisterFunction>(PluginInterface::getRegisterFunctionName());
  if (register_function == NULL)
    throw Exception(UnicodeString("No register function with signature: '") + PluginInterface::getRegisterFunctionName() + "' found in module: " + glue_cast<UnicodeString>(module_path));

  register_function(this);

  loaded_modules.insert(std::make_pair(module_path, dll_module));

  return dll_module;
}

} /* namespace mru */

#endif

