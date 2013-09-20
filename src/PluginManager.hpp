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
  typedef AbstractPluginFactory<PluginInterface, IdType> AbstractPluginFactory;
  typedef boost::shared_ptr<Self> Pointer;
  typedef typename AbstractPluginFactory::PluginPointer PluginPointer;
  
  static void destroyPlugin(PluginInterface *plugin_pointer)
  {
    delete plugin_pointer;
  }

  static Self::Pointer
  createFactory(const IdType &id)
  {
    return boost::shared_ptr<PluginFactory>(allocateFactory(id), &Self::destroyFactory);
  }

  static Self *
  allocateFactory(const IdType &id)
  {
    Self *new_factory = new Self(id);
    return new_factory;
  }

  static void
  destroyFactory(AbstractPluginFactory *factory_pointer)
  {
    delete factory_pointer;
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

  typedef std::list<typename AbstractPluginFactory::Pointer> FactoryList;
  typedef void (*DestroyFunction)(AbstractPluginFactory *factory_pointer);
public:
  PluginManager(void);
  virtual ~PluginManager(void);
  void registerFactory(typename AbstractPluginFactory::Pointer factory); 
  void registerFactory(AbstractPluginFactory *factory_pointer, DestroyFunction destroy_function); 
  PluginPointer createPlugin(const IdType &id);
  FactoryList getFactoryList(void);

protected:
  PluginManager(const PluginManager &); //disabled
  PluginManager& operator=(const PluginManager &); //disabled

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
      return PluginFactory<PluginClass, PluginInterface>::createFactory(TagId); \
    } \
  };

#endif /* PLUGIN_MANAGER_HPP */

