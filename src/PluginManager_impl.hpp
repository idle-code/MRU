#ifndef PLUGIN_MANAGER_IMPL_HPP
  #error "This is implementation file. Use PluginManager.hpp instead"
#else

namespace mru
{

template<typename PluginInterface, typename IdType>
typename PluginManager<PluginInterface, IdType>::Pointer
PluginManager<PluginInterface, IdType>::create(void)
{
  return boost::make_shared< PluginManager<PluginInterface, IdType> >();
}

template<typename PluginInterface, typename IdType>
PluginManager<PluginInterface, IdType>::PluginManager(void)
{ }

template<typename PluginInterface, typename IdType>
PluginManager<PluginInterface, IdType>::~PluginManager(void)
{
}

template<typename PluginInterface, typename IdType>
void
PluginManager<PluginInterface, IdType>::registerFactory(AbstractPluginFactory *factory_pointer, DestroyFunction destroy_function)
{
  typename AbstractPluginFactory::Pointer factory(factory_pointer, destroy_function);
  registerFactory(factory);
}

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

template<typename PluginInterface, typename IdType>
std::list<typename PluginManager<PluginInterface, IdType>::AbstractPluginFactory::Pointer>
PluginManager<PluginInterface, IdType>::getFactoryList(void)
{
  std::list<typename PluginManager<PluginInterface, IdType>::AbstractPluginFactory::Pointer> factory_list;
  for(typename FactoryMap::iterator i = factory_map.begin(); i != factory_map.end(); ++i)
    factory_list.push_back(i->second);
  return factory_list;
}

template<typename PluginInterface, typename IdType>
const std::map<IdType, typename PluginManager<PluginInterface, IdType>::AbstractPluginFactory::Pointer> &
PluginManager<PluginInterface, IdType>::getFactoryMap(void)
{
  return factory_map;
}

} /* namespace mru */

#endif /* PLUGIN_MANAGER_IMPL_HPP */

