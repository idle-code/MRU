//TODO: add include guard

namespace mru
{

template<typename interface_type>
plugin_manager<interface_type>::plugin_manager(void)
{ }

template<typename interface_type>
plugin_manager<interface_type>::~plugin_manager(void)
{
  typename std::map<interface_type*, typeinfo_type>::iterator plugin_iterator = m_plugins.begin();
  while(plugin_iterator != m_plugins.end()) {
    free_instance((*plugin_iterator).first);
    m_plugins.erase(plugin_iterator);
    plugin_iterator = m_plugins.begin();
  }

  typename std::map<typeinfo_type, abstract_plugin_factory*>::iterator factory_iterator = m_factories.begin();
  while(factory_iterator != m_factories.end()) {
    m_factories.erase(factory_iterator);  
    factory_iterator = m_factories.begin();
  }
}

//template<typename interface_type>
//void
//plugin_manager<interface_type>::register_instance(typeinfo_type a_typeinfo, interface_type *a_instance)
//{
//  //FIXME: implement
//  m_factories.push_back(make_pair(a_typeinfo, a_instance));
//}

template<typename interface_type>
void
plugin_manager<interface_type>::register_factory(abstract_plugin_factory *a_factory)
{
  VAL(a_factory->get_typeinfo());
  m_factories.insert(std::make_pair(a_factory->get_typeinfo(), a_factory));
}

template<typename interface_type>
std::list<typename plugin_manager<interface_type>::typeinfo_type>
plugin_manager<interface_type>::available_plugins(void) const
{
  std::list<typeinfo_type> result;
  typename std::map<typeinfo_type, abstract_plugin_factory*>::const_iterator ci = m_factories.begin();
  for(; ci != m_factories.end(); ++ci) {
    result.push_back(ci->first);
  }
  return result;
}

template<typename interface_type>
interface_type *
plugin_manager<interface_type>::get_instance(typeinfo_type a_typeinfo)
{
  VAL(a_typeinfo);
  VAL(m_factories.size());
  if(m_factories.count(a_typeinfo) == 0)
    return NULL;
  
  interface_type *instance = m_factories[a_typeinfo]->get_instance();
  m_plugins.insert(std::make_pair(instance, a_typeinfo));
  VAL(instance);
  return instance;
}

template<typename interface_type>
void
plugin_manager<interface_type>::free_instance(interface_type *a_instance)
{
  //FIXME: implement
  typename std::map<interface_type*, typeinfo_type>::iterator i = m_plugins.find(a_instance);
  if(i == m_plugins.end())
    delete a_instance; //FIXME: if there is no record of this plugin - it could be created by other means... throw?
  else {
    abstract_plugin_factory *factory = m_factories[(*i).second];
    factory->free_instance(a_instance);
    m_plugins.erase(i);
  }
  a_instance = NULL;
}

/* ------------------------------------------------------------------------- */

template<typename interface_type>
plugin_manager<interface_type>::abstract_plugin_factory::abstract_plugin_factory(typeinfo_type a_typeinfo)
  : m_typeinfo(a_typeinfo)
{ }

template<typename interface_type>
plugin_manager<interface_type>::abstract_plugin_factory::~abstract_plugin_factory(void)
{ }

template<typename interface_type>
const typename plugin_manager<interface_type>::typeinfo_type &
plugin_manager<interface_type>::abstract_plugin_factory::get_typeinfo(void) const
{
  return m_typeinfo;
}

/* ------------------------------------------------------------------------- */

template<typename interface_type>
template<typename implementation_type>
plugin_manager<interface_type>::plugin_factory<implementation_type>::plugin_factory(typeinfo_type a_typeinfo)
  : abstract_plugin_factory(a_typeinfo)
{ }

template<typename interface_type>
template<typename implementation_type>
plugin_manager<interface_type>::plugin_factory<implementation_type>::~plugin_factory(void)
{ }


template<typename interface_type>
template<typename implementation_type>
implementation_type *
plugin_manager<interface_type>::plugin_factory<implementation_type>::get_instance(void)
{
  return new implementation_type();
}

template<typename interface_type>
template<typename implementation_type>
void
plugin_manager<interface_type>::plugin_factory<implementation_type>::free_instance(interface_type *a_instance)
{
  if(a_instance != NULL) {
    delete static_cast<implementation_type*>(a_instance); //CHECK: is static_cast sufficient here?
    a_instance = NULL;
  }
}

} /* namespace mru */

