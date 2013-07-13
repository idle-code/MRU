#ifndef INPUT_PLUGIN_HPP
#define INPUT_PLUGIN_HPP

#include "plugins/MruPlugin.hpp"
#include "FileIterator.hpp"
#include <boost/shared_ptr.hpp>

namespace mru
{

class InputPlugin : public MruPlugin {
public:
  typedef InputPlugin self_type;
public:
  PLUGIN_INTERFACE("InputPlugin")
  InputPlugin(const name_type &a_name)
    : MruPlugin(static_interface_name(), a_name)
  { }

  virtual FileIterator::Pointer getFileIterator(const FilePath &a_path) = 0;

  void includeFiles(bool include)
  {
    m_include_files = include;
  }

  void includeDirectories(bool include)
  {
    m_include_directories = include;
  }
  
  void searchRecursively(bool search)
  {
    m_search_recursively = search;
  }

  bool includeFiles(void)
  {
    return m_include_files;
  }

  bool includeDirectories(void)
  {
    return m_include_directories;
  }

  bool searchRecursively(void)
  {
    return m_search_recursively;
  }

private:
  bool m_include_files;
  bool m_include_directories;
  bool m_search_recursively;
};

typedef plugin_manager<InputPlugin> InputPluginManager;

} /* namespace mru */

#endif /* INPUT_PLUGIN_HPP */

