#ifndef GENERICBOOSTFSDRIVER_HPP
#define GENERICBOOSTFSDRIVER_HPP

#include <plugins/filesystem_plugin.hpp>

namespace mru
{

class GenericBoostFSDriver : public FilesystemPlugin {
public:
  typedef GenericBoostFSDriver self_type;
public:
  PLUGIN_NAME("GenericBoostFSDriver");
  GenericBoostFSDriver(void);
  ~GenericBoostFSDriver(void);

};

} /* namespace mru */

#endif /* GENERICBOOSTFSDRIVER_HPP */

