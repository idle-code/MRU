#ifndef INPUT_PLUGIN_HPP
#define INPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class InputPlugin : public MruPlugin {
public:
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

typedef PluginManager<InputPlugin> InputPluginManager;

} /* namespace mru */

#define EXPORT_INPUT_PLUGIN_FACTORY(factory) \
  extern "C" { \
    void register_input_plugin(InputPluginManager::Pointer plugin_manager) { \
      assert(plugin_manager); \
      plugin_manager->registerFactory(factory); \
    } \
  }

#endif /* INPUT_PLUGIN_HPP */

