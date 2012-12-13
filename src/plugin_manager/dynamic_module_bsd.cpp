#include <dynamic_module_bsd.hpp>
#include <dlfcn.h>
#include <libgen.h>

#include <debug_l.h>

namespace mru
{

const filename_type dynamic_module_bsd::m_prefix = "lib";
const filename_type dynamic_module_bsd::m_postfix = ".so";

dynamic_module_bsd::dynamic_module_bsd(void)
  : dynamic_module()
{
}

dynamic_module_bsd::~dynamic_module_bsd(void)
{
  unload();
}

bool
dynamic_module_bsd::load(const filepath_type &a_file_path)
{
  //VAL(a_file_path);
  name_type path = dirname(a_file_path.c_str());
  //VAL(path);
  name_type filename = basename(a_file_path.c_str());
  //VAL(filename);
  if(filename.substr(0, m_prefix.length()) != m_prefix)
    filename = m_prefix + filename;
  if(filename.substr(filename.length() - m_prefix.length()) != m_postfix)
    filename += m_postfix;
  name_type full_name = path + "/" + filename;
  //VAL(full_name);
  m_module_handle = dlopen(full_name.c_str(), RTLD_NOW);
  if(m_module_handle == NULL) {
    ERR("Error while loading dynamic module (bsd): " << dlerror());
    return false;
  }
  return true;
}

bool
dynamic_module_bsd::unload(void)
{
  if(m_module_handle != NULL) {
    if(0 != dlclose(m_module_handle)) {
      ERR("Error while closing dynamic module (bsd): " << dlerror());
      m_module_handle = NULL;
      return false;
    }
    m_module_handle = NULL;
  }
  return true;
}

bool
dynamic_module_bsd::is_loaded(void) const
{
  return m_module_handle != NULL;
}

void*
dynamic_module_bsd::get_symbol(const name_type &a_symbol)
{
  //FO("dynamic_module_bsd::get_symbol(const name_type &a_symbol)");
  if(m_module_handle == NULL) {
    ERR("Error while importing symbol from dynamic module (bsd): Module not loaded");
    return NULL;
  }
  return dlsym(m_module_handle, a_symbol.c_str());
}

const filename_type
dynamic_module_bsd::filename_prefix(void) const
{
  return m_prefix;
}

const filename_type
dynamic_module_bsd::filename_postfix(void) const
{
  return m_postfix;
}

} /* namespace mru */
