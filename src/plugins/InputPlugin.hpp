#ifndef INPUT_PLUGIN_HPP
#define INPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class InputPluginException : public MruPlugin::Exception {
public:
  InputPluginException(const UnicodeString &message)
    : MruPlugin::Exception("InputPlugin", message)
  { }
  InputPluginException(const std::string &message)
    : MruPlugin::Exception("InputPlugin", message)
  { }
};

/* ------------------------------------------------------------------------- */

class InputPlugin : public MruPlugin {
public:
  PLUGIN_INTERFACE("InputPlugin")
  InputPlugin(const name_type &name)
    : MruPlugin(static_interface_name(), name)
  { }

  virtual FileIterator::Pointer getFileIterator(const FilePath &path) = 0;

  void includeFiles(bool include)
  {
    include_files = include;
  }
  bool includeFiles(void)
  {
    return include_files;
  }

  void includeDirectories(bool include)
  {
    include_directories = include;
  }
  bool includeDirectories(void)
  {
    return include_directories;
  }
  
  void searchRecursively(bool search)
  {
    search_recursively = search;
  }
  bool searchRecursively(void)
  {
    return search_recursively;
  }

private:
  bool include_files;
  bool include_directories;
  bool search_recursively;
};

typedef plugin_manager<InputPlugin> InputPluginManager;

} /* namespace mru */

#endif /* INPUT_PLUGIN_HPP */

