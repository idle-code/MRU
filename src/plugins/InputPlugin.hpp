#ifndef INPUT_PLUGIN_HPP
#define INPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class InputPlugin : public MruPlugin {
public:
  typedef PluginManager<InputPlugin> Manager;
  typedef void (*RegisterFunctionType)(Manager::Pointer);
  static const char* RegisterFunctionName(void) { return "registerInputPluginFactory"; }

  MODULE_EXCEPTION(InputPlugin, MruPlugin::Exception);
  typedef boost::shared_ptr<InputPlugin> Pointer;

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

} /* namespace mru */

#endif /* INPUT_PLUGIN_HPP */

