#include "plugin_manager.hpp"


namespace mru
{

/* ------------------------------------------------------------------------- */

generic_plugin_info::generic_plugin_info(const name_type &a_interface, const name_type &a_name)
  : m_interface_name(a_interface), m_implementation_name(a_name)
{ }

generic_plugin_info::~generic_plugin_info(void)
{ }

const name_type &
generic_plugin_info::interface_name(void) const
{
  return m_interface_name;
}

const name_type &
generic_plugin_info::implementation_name(void) const
{
  return m_implementation_name;
}

void
generic_plugin_info::destroy(void)
{
  delete this;
}

/* ------------------------------------------------------------------------- */

generic_plugin_factory::generic_plugin_factory(const name_type &a_interface, const name_type &a_name)
  : generic_plugin_info(a_interface, a_name)
{ }

/* ------------------------------------------------------------------------- */

generic_plugin_manager::generic_plugin_manager(const name_type &a_interface)
  : generic_plugin_info(a_interface, a_interface + "_manager")
{ }

/* ------------------------------------------------------------------------- */
plugin_factory_distributor::plugin_factory_distributor(void)
{ }

plugin_factory_distributor::~plugin_factory_distributor(void)
{
  //FO("plugin_factory_distributor::~plugin_factory_distributor(void)");
  std::map<name_type, generic_plugin_manager*>::iterator i = m_plugin_managers.begin();
  while(i != m_plugin_managers.end()) {
    unregister_manager(i->second);
    i = m_plugin_managers.begin();
  } 
}

void
plugin_factory_distributor::destroy(void)
{
  plugin_factory_distributor::destroy_instance();
}

bool
plugin_factory_distributor::register_factory(generic_plugin_factory *a_factory)
{
  //FO("bool plugin_factory_distributor::register_factory(generic_plugin_factory *a_factory)");
  if(a_factory == NULL)
    return false;
  
  //VAL(a_factory->implementation_name());
  if(m_plugin_managers.find(a_factory->interface_name()) == m_plugin_managers.end()) {
    WARN("Unknown type of plugin factory: " << a_factory->interface_name());
    a_factory->destroy();
    return false;
  }

  //VAL(a_factory->interface_name());
  //VAL(m_plugin_managers[a_factory->interface_name()]);
  m_plugin_managers[a_factory->interface_name()]->register_factory(a_factory);

  return true;
}

bool
plugin_factory_distributor::register_manager(generic_plugin_manager *a_manager)
{
  //FO("bool plugin_factory_distributor::register_manager(generic_plugin_manager *a_manager)");
  if(a_manager == NULL)
    return false;
  
  //VAL(a_manager->interface_name());
  if(m_plugin_managers.find(a_manager->interface_name()) != m_plugin_managers.end()) {
    ERR("Manager with type \'" << a_manager->interface_name() << "\' is already in registered");
    return false;
  }

  m_plugin_managers.insert(std::make_pair(a_manager->interface_name(), a_manager));

  return true;
}

bool
plugin_factory_distributor::unregister_manager(generic_plugin_manager *a_manager)
{
  //FO("bool plugin_factory_distributor::unregister_manager(generic_plugin_manager *a_manager)");
  if(a_manager == NULL)
    return false;
  
  //VAL(a_manager->interface_name());
  std::map<name_type, generic_plugin_manager*>::iterator to_remove = m_plugin_managers.find(a_manager->interface_name());
  if(to_remove == m_plugin_managers.end()) {
    ERR("There is no registered manager with type \'" << a_manager->interface_name() << "\'");
    return false;
  }

  m_plugin_managers.erase(to_remove);

  if(m_plugin_managers.size() < 1)
    destroy();

  return true;
}

} /* namespace mru */

