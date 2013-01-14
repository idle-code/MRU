#ifndef GENERICBOOST_HPP
#define GENERICBOOST_HPP

#include "plugins/output_plugin.hpp"

namespace GenericBoost_OutputPlugin
{

using mru::filepath_type;

class GenericBoost : public mru::OutputPlugin {
public:
  typedef GenericBoost self_type;
public:
  PLUGIN_NAME("GenericBoost")
  GenericBoost(void);
  ~GenericBoost(void);

  filepath_type get_directory(void);
  bool change_directory(const filepath_type &a_path);
  bool rename(const filepath_type &a_name, const filepath_type &a_new_name);

protected:
  filepath_type m_current_directory;
};

} /* namespace GenericBoost_OutputPlugin */

#endif /* GENERICBOOST_HPP */

