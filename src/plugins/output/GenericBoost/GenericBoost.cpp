#include "GenericBoost.hpp"

namespace GenericBoost_OutputPlugin
{

GenericBoost::GenericBoost(void)
  : mru::OutputPlugin(static_implementation_name())
{ }

GenericBoost::~GenericBoost(void)
{ }

bool
GenericBoost::change_directory(const filepath_type &a_path)
{
  FO("GenericBoost::change_directory(const filepath_type &a_path)");

  return true;
}

bool
GenericBoost::rename(const filepath_type &a_name, const filepath_type &a_new_name)
{
  FO("GenericBoost::rename(const filepath_type &a_name, const filepath_type &a_new_name)");

  return true;
}

} /* namespace GenericBoost_OutputPlugin */

EXPORT_START
  EXPORT_PLUGIN(GenericBoost_OutputPlugin::GenericBoost)
EXPORT_END

