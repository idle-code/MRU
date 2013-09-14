#ifndef CORE_HPP
#define CORE_HPP

#include "plugins/UiPlugin.hpp"
#include "plugins/InputPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/MetatagPlugin.hpp"

#include "types.hpp"
#include "patterns.hpp"
#include "FileIterator.hpp"
#include <sigc++/sigc++.h>
#include <boost/filesystem.hpp>
#include "Metatag/Expression.hpp"
#include <pthread.h>
#include "MruException.hpp"

namespace mru {

class MruCore : public singleton<MruCore> {
public:
  typedef MruCore self_type;
  typedef boost::shared_ptr<MruCore> Pointer;

  MODULE_EXCEPTION(MruCore, MruException);
  
public: // generic methods
  MruCore(void);
  ~MruCore(void);

  void loadConfiguration(const FilePath &configuration_file);

  int start(int argc, char **argv);

  UiPlugin::Pointer getUiPlugin(void);
  void setUiPlugin(UiPlugin::Pointer plugin);

  OutputPlugin::Pointer getOutputPlugin(void);
  void setOutputPlugin(OutputPlugin::Pointer plugin);

  InputPlugin::Pointer getInputPlugin(void);
  void setInputPlugin(InputPlugin::Pointer plugin);

public: // program state/configuration
  void setDirectory(const FilePath &directory);
  const FilePath getDirectory(void) const;
  sigc::signal<void, FilePath> SignalDirectoryChanged;
  
  void setFileFilter(const UnicodeString &filter);
  const UnicodeString& getFileFilter(void);
  sigc::signal<void, UnicodeString> SignalFileFilterChanged;

  void setMetatagExpression(Metatag::Expression::Pointer expression);
  Metatag::Expression::Pointer getMetatagExpression(void);
  sigc::signal<void, const Metatag::Expression::Pointer> SignalMetatagExpressionChanged;

  FileIterator::Pointer getIterator(void);
  FilePath generateNewFilepath(const FileIterator::Pointer file_iterator);

public: // ranaming process
  void resetState(void);
  void startRename(void);
  sigc::signal<void> SignalRenameStarted;
  void stopRename(void);
  sigc::signal<void> SignalRenameStopped;

  sigc::signal<void, FilePath, FilePath> SignalFilenameChange;

private:
  void loadDefaultConfiguration(void);
  void saveConfiguration(void);
  void applyConfiguration(void);
  template<typename PluginType>
  void loadAllModulesIn(const FilePath &directory, typename PluginType::Manager::Pointer plugin_manager);
  template<typename PluginType>
  void loadModule(const FilePath &module_path, typename PluginType::Manager::Pointer plugin_manager);
  std::list<FilePath> listFilesInDirectory(const FilePath &directory);

private:
  boost::property_tree::ptree reg;
  UiPlugin::Pointer ui_plugin;
  InputPlugin::Pointer input_plugin;
  OutputPlugin::Pointer output_plugin;

  InputPlugin::Manager::Pointer input_plugin_manager;
  OutputPlugin::Manager::Pointer output_plugin_manager;
  UiPlugin::Manager::Pointer ui_plugin_manager;
  MetatagPluginManager::Pointer metatag_plugin_manager;

  Metatag::Expression::Pointer metatag_expression;
};

} /* namespace mru */

#endif /* CORE_HPP */

