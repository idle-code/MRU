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
      m_create_new_path(false), m_overwrite_target(false),
      m_rename_mode(ModeRename)
  { }

  virtual void createDirectory(const FilePath &a_path) = 0;
  virtual void removeDirectory(const FilePath &a_path) = 0;

  virtual void moveFile(const FilePath &a_source_path, const FilePath &a_destination_path) = 0;
  virtual void moveDirectory(const FilePath &a_source_path, const FilePath &a_destination_path) = 0;

  virtual bool fileExists(const FilePath &a_path) const = 0;
  virtual bool directoryExists(const FilePath &a_path) const = 0;

  virtual bool exists(const FilePath &a_path) const
  {
    return directoryExists(a_path) || fileExists(a_path);
  }

  void createNewPath(bool create)
  {
    m_create_new_path = create;
  }
  bool createNewPath(void) const
  {
    return m_create_new_path;
  }

  void overwriteTarget(bool overwrite)
  {
    m_overwrite_target = overwrite;
  }
  bool overwriteTarget(void) const
  {
    return m_overwrite_target;
  }

  typedef enum { ModeRename, ModeCopy, ModeLink, ModeNone } RenameModeKind;
  void setRenameMode(RenameModeKind mode)
  {
    m_rename_mode = mode;
  }
  RenameModeKind getRenameMode(void) const
  {
    return m_rename_mode;
  }
private:
  bool m_create_new_path;
  bool m_overwrite_target;
  RenameModeKind m_rename_mode;
};

typedef plugin_manager<OutputPlugin> OutputPluginManager;

} /* namespace mru */

#endif /* OUTPUT_PLUGIN_HPP */

