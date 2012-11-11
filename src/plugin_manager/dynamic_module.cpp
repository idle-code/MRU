#include <dynamic_module.hpp>
#include <dynamic_module_bsd.hpp>

namespace mru
{

dynamic_module*
dynamic_module::load(const name_type &a_file_path)
{
  //TODO: add some #ifdef for working on windows
  return new dynamic_module_bsd(a_file_path);
}

/* ------------------------------------------------------------------------- */

dynamic_module::dynamic_module(const name_type &a_file_path)
  : m_file_path(a_file_path)
{ }

dynamic_module::~dynamic_module(void)
{ }

const dynamic_module::name_type &
dynamic_module::filepath(void) const
{
  return m_file_path;
}

const dynamic_module::name_type &
dynamic_module::filename_prefix(void) const
{
  return "";
}

const dynamic_module::name_type &
dynamic_module::filename_postfix(void) const
{
  return "";
}

} /* namespace mru */
