#ifndef OUTPUT_PLUGIN_HPP
#define OUTPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"

namespace mru
{

/* ------------------------------------------------------------------------- */

class OutputPlugin : public MruPlugin {
public:
  typedef PluginManager<OutputPlugin> Manager;
  typedef DynamicPluginManager<OutputPlugin> DynamicManager;
  typedef void (*RegisterFunctionType)(Manager::Pointer);
  static const char* getRegisterFunctionName(void) { return "register_output_plugin"; }

  typedef boost::shared_ptr<OutputPlugin> Pointer;
  MODULE_EXCEPTION(OutputPlugin, MruPlugin::Exception);

  OutputPlugin(void)
    : create_new_path(false), override_target(false)
  { }

  virtual void createDirectory(const FilePath &path) = 0;
  virtual void removeDirectory(const FilePath &path) = 0;

  virtual bool exists(const FilePath &path) const = 0;

  virtual void move(const FilePath &source_path, const FilePath &destination_path) = 0;
  virtual void copy(const FilePath &source_path, const FilePath &destination_path) = 0;
  virtual void link(const FilePath &source_path, const FilePath &destination_path) = 0;
  virtual FilePath resolveLink(const FilePath &path) const = 0;

  void createNewPath(bool create)
  {
    create_new_path = create;
  }
  bool createNewPath(void) const
  {
    return create_new_path;
  }

  void overrideTarget(bool override)
  {
    override_target = override;
  }
  bool overrideTarget(void) const
  {
    return override_target;
  }

private:
  bool create_new_path;
  bool override_target;
};

} /* namespace mru */

#endif /* OUTPUT_PLUGIN_HPP */

