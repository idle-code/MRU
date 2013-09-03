#ifndef PLUGIN_MANAGER_IMPL_HPP
  #error "This is implementation file. Use PluginManager.hpp instead"
#else

namespace mru
{

template<typename PluginInterface, typename IdType>
PluginManager<PluginInterface, IdType>::PluginManager(void)
{ }

template<typename PluginInterface, typename IdType>
void
PluginManager<PluginInterface, IdType>::registerFactory(typename AbstractPluginFactory::Pointer factory)
{
  if (!factory)
    throw Exception("Null factory provided");

  typename FactoryMap::iterator plugin_factory = factory_map.find(factory->getId());
  if (plugin_factory != factory_map.end())
    throw Exception("Factory already registered for specified id");
  factory_map.insert(std::make_pair(factory->getId(), factory));
}

template<typename PluginInterface, typename IdType>
typename PluginManager<PluginInterface, IdType>::PluginPointer
PluginManager<PluginInterface, IdType>::createPlugin(const IdType &id)
{
  typename FactoryMap::iterator plugin_factory = factory_map.find(id);
  if (plugin_factory == factory_map.end())
    throw Exception("No factory registered for specified id");
  return (*plugin_factory).second->createPlugin();
}

} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

