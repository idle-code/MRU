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

const filepath_type &
dynamic_module::filepath(void) const
{
  return m_file_path;
}

const filename_type
dynamic_module::filename_prefix(void) const
{
  return "";
}

const filename_type
dynamic_module::filename_postfix(void) const
{
  return "";
}

/* ------------------------------------------------------------------------- */

dynamic_module *
dynamic_module_manager::load(const name_type &a_file_path)
{
  if(a_file_path.length() < 1)
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
  m_loaded_modules.erase(m_loaded_modules.find(a_module->filepath()));
  a_module->unload();
  delete a_module;
  a_module = NULL;
}


} /* namespace mru */
