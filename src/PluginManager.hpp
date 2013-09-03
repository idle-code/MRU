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
  virtual PluginPointer createPlugin(void) = 0;
  virtual IdType getId(void) const = 0;
};

template<typename PluginClass, typename PluginInterface, typename IdType=std::string>
class PluginFactory : public AbstractPluginFactory<PluginInterface, IdType> {
public:
  typedef AbstractPluginFactory<PluginInterface, IdType> Parent;
  typedef boost::shared_ptr< PluginFactory<PluginClass, PluginInterface, IdType> > Pointer;
  typedef typename Parent::PluginPointer PluginPointer;

  static Pointer
  create(const IdType &id)
  {
    return boost::make_shared<PluginFactory>(id);
  }
public:

  PluginFactory(const IdType &id)
    : id(id) { }

  PluginPointer
  createPlugin(void)
  {
    return boost::make_shared<PluginClass>();
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
  class Exception;
public:
  PluginManager(void);
  void registerFactory(typename AbstractPluginFactory::Pointer factory); 
  PluginPointer createPlugin(const IdType &id);

private:
  PluginManager(const PluginManager &); //disabled

  typedef std::map<IdType, typename AbstractPluginFactory::Pointer> FactoryMap;
  FactoryMap factory_map;
};

template<typename PluginInterface, typename IdType>
class PluginManager<PluginInterface, IdType>::Exception : public MruException {
public:
  Exception(const UnicodeString &message) throw()
    : MruException(message)
  { }
  
  ~Exception(void) throw()
  { }
};

} /* namespace mru */

#define PLUGIN_MANAGER_IMPL_HPP
#include "PluginManager_impl.hpp"
#undef PLUGIN_MANAGER_IMPL_HPP

#endif /* PLUGIN_MANAGER_HPP */

