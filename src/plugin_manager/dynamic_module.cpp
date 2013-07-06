#include <dynamic_module.hpp>
#include <dynamic_module_bsd.hpp>
#include <utility>

namespace mru
{

/* ------------------------------------------------------------------------- */

dynamic_module::dynamic_module(void)
  : m_file_path()
{ }

dynamic_module::~dynamic_module(void)
{ }

const std::string &
dynamic_module::filepath(void) const
{
  return m_file_path;
}

const std::string
dynamic_module::filename_prefix(void) const
{
  return "";
}

const std::string
dynamic_module::filename_postfix(void) const
{
  return "";
}

/* ------------------------------------------------------------------------- */

dynamic_module_manager::dynamic_module_manager(void)
{ }

dynamic_module_manager::~dynamic_module_manager(void)
{ }

dynamic_module *
dynamic_module_manager::load(const std::string &a_file_path)
{
  if(a_file_path.empty())
    return NULL;
  dynamic_module* new_module = NULL;
  if(m_loaded_modules.find(a_file_path) == m_loaded_modules.end()) {
    new_module = new dynamic_module_bsd();
    if(new_module == NULL)
      return NULL;
    if(!new_module->load(a_file_path)) {
      delete new_module;
      return NULL;
    }
    m_loaded_modules.insert(std::make_pair(a_file_path, new_module));
  } else {
    new_module = m_loaded_modules[a_file_path];
  } 
  return new_module;
}

void
dynamic_module_manager::unload(dynamic_module *&a_module)
{
  if(a_module == NULL)
    return;
  std::map<std::string, dynamic_module*>::iterator to_remove = m_loaded_modules.find(a_module->filepath());
  if(to_remove == m_loaded_modules.end())
    return;
  m_loaded_modules.erase(to_remove);
  a_module->unload();
  delete a_module;
  a_module = NULL;
}

void
dynamic_module_manager::unload_all(void)
{
  for(std::map<std::string, dynamic_module*>::iterator i = m_loaded_modules.begin(); i != m_loaded_modules.end(); ++i) {
    unload((*i).second);
  }
  m_loaded_modules.clear();
}

} /* namespace mru */

