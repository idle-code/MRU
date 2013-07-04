#include "GenericBoost.hpp"
#include "glue.hpp"

namespace GenericBoost_OutputPlugin
{

namespace bfs = boost::filesystem;

GenericBoost::GenericBoost(void)
  : mru::OutputPlugin(static_implementation_name()), m_current_directory("/")
{ }

GenericBoost::~GenericBoost(void)
{ }

filepath_type
GenericBoost::get_directory(void)
{
  //FO("GenericBoost::get_directory(void)");
  return m_current_directory;
}

bool
GenericBoost::change_directory(const filepath_type &a_path)
{
  FO("GenericBoost::change_directory(const filepath_type &a_path)");

  return true;
}

bool
GenericBoost::rename(const filepath_type &a_old_path, const filepath_type &a_new_path)
{
  FO("GenericBoost::rename(const filepath_type &a_old_path, const filepath_type &a_new_path)");
  if(a_old_path == a_new_path)
    return false;

  if(bfs::exists(a_new_path))
    throw std::runtime_error("Cannot rename: \"" + mru::glue_cast<std::string>(a_old_path) + "\"\nDestination file: \"" + mru::glue_cast<std::string>(a_new_path) + "\" already exists");
  bfs::rename(a_old_path, a_new_path);  

  return true;
}

} /* namespace GenericBoost_OutputPlugin */

EXPORT_START
  EXPORT_PLUGIN(GenericBoost_OutputPlugin::GenericBoost)
EXPORT_END

