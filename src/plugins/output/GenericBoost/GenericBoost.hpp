#ifndef GENERICBOOST_HPP
#define GENERICBOOST_HPP

#include "plugins/output_plugin.hpp"

namespace GenericBoost_OutputPlugin
{

using namespace mru;

class GenericBoost : public mru::OutputPlugin {
public:
  typedef GenericBoost self_type;
public:
  PLUGIN_NAME("GenericBoost")
  GenericBoost(void);
  ~GenericBoost(void);

  bool change_directory(const filepath_type &a_path);
  bool rename(const filepath_type &a_name, const filepath_type &a_new_name);

protected:
  /* data */
};

} /* namespace GenericBoost_OutputPlugin */

#endif /* GENERICBOOST_HPP */

