#ifndef PLUGIN_MANAGER_HPP
#define PLUGIN_MANAGER_HPP
 
#include "MruException.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <map>

namespace mru
{

template<typename PluginInterface, typename IdType=std::string>
class AbstractPluginFactory {
public:
  typedef boost::shared_ptr< AbstractPluginFactory<PluginInterface, IdType> > Pointer;
  typedef boost::shared_ptr<PluginInterface> PluginPointer;
public:
  virtual ~AbstractPluginFactory(void) { }
  virtual PluginPointer createPlugin(void) = 0;
  virtual IdType getId(void) const = 0;
};

template<typename PluginClass, typename PluginInterface, typename IdType=std::string>
class PluginFactory : public AbstractPluginFactory<PluginInterface, IdType> {
public:
  typedef PluginFactory<PluginClass, PluginInterface, IdType> Self;
  typedef AbstractPluginFactory<PluginInterface, IdType> Parent;
  typedef boost::shared_ptr<Self> Pointer;
  typedef typename Parent::PluginPointer PluginPointer;
  
  static void destroyFactory(Self *&factory_pointer)
  {
    FO("static void destroyFactory(Self *factory_pointer)");
    VAL(factory_pointer);
    delete factory_pointer;
    factory_pointer = NULL;
  }

  static void destroyPlugin(PluginInterface *plugin_pointer)
  {
    delete plugin_pointer;
  }

  static Self::Pointer
  createSharedFactory(const IdType &id)
  {
    return boost::shared_ptr<PluginFactory>(new Self(id), &Self::destroyFactory);
  }

  static Self *
  createFactory(const IdType &id)
  {
    return new Self(id);
  }
public:
  PluginFactory(const IdType &id)
    : id(id) { }

  PluginPointer
  createPlugin(void)
  {
    return boost::shared_ptr<PluginClass>(new PluginClass(), &Self::destroyPlugin);
  }

  IdType
  getId(void) const
  {
    return id;
  }

private:
  IdType id;
};

/* ------------------------------------------------------------------------- */

template<typename PluginInterface, typename IdType=std::string>
class PluginManager {
public:
  typedef boost::shared_ptr< PluginManager<PluginInterface, IdType> > Pointer;
  typedef AbstractPluginFactory<PluginInterface, IdType> AbstractPluginFactory;
  typedef typename AbstractPluginFactory::PluginPointer PluginPointer;
  MODULE_EXCEPTION(PluginManager, MruException);
  static Pointer create(void);
public:
  PluginManager(void);
  void registerFactory(typename AbstractPluginFactory::Pointer factory); 
  PluginPointer createPlugin(const IdType &id);
  std::list<typename AbstractPluginFactory::Pointer> getFactoryList(void);

private:
  PluginManager(const PluginManager &); //disabled

  typedef std::map<IdType, typename AbstractPluginFactory::Pointer> FactoryMap;
  FactoryMap factory_map;
};

} /* namespace mru */

#define PLUGIN_MANAGER_IMPL_HPP
#include "PluginManager_impl.hpp"
#undef PLUGIN_MANAGER_IMPL_HPP

#define PLUGIN_FACTORY(PluginClass, PluginInterface, TagId) \
  class Factory : public PluginFactory<PluginClass, PluginInterface> { \
  public: \
    static Pointer create(void) { \
      return PluginFactory<PluginClass, PluginInterface>::create(TagId); \
    } \
  };

#endif /* PLUGIN_MANAGER_HPP */

