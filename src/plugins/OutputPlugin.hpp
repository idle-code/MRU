#ifndef OUTPUT_PLUGIN_HPP
#define OUTPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"

namespace mru
{

class OutputPluginException : public MruPluginException {
public:
  OutputPluginException(const std::string &a_message)
    : MruPluginException("OutputPlugin", a_message)
  { }
};

/* ------------------------------------------------------------------------- */

class OutputPlugin : public MruPlugin {
public:
  PLUGIN_INTERFACE("OutputPlugin")
  OutputPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name),
      m_create_new_path(false), m_override_target(false)
  { }

  virtual void createDirectory(const FilePath &a_path) = 0;
  virtual void removeDirectory(const FilePath &a_path) = 0;

  virtual bool exists(const FilePath &a_path) const = 0;

  virtual void move(const FilePath &a_source_path, const FilePath &a_destination_path) = 0;
  virtual void copy(const FilePath &a_source_path, const FilePath &a_destination_path) = 0;
  virtual void link(const FilePath &a_source_path, const FilePath &a_destination_path) = 0;
  virtual FilePath resolveLink(const FilePath &a_path) const = 0;

  void createNewPath(bool create)
  {
    m_create_new_path = create;
  }
  bool createNewPath(void) const
  {
    return m_create_new_path;
  }

  void overrideTarget(bool override)
  {
    m_override_target = override;
  }
  bool overrideTarget(void) const
  {
    return m_override_target;
  }

private:
  bool m_create_new_path;
  bool m_override_target;
};

typedef plugin_manager<OutputPlugin> OutputPluginManager;

} /* namespace mru */

#endif /* OUTPUT_PLUGIN_HPP */

