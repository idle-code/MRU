#ifndef CORE_HPP
#define CORE_HPP

#include "plugins/UiPlugin.hpp"
#include "plugins/InputPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/MetatagPlugin.hpp"

#include "FilteringFileIterator.hpp"
#include <unicode/regex.h>
#include "SortingFileIterator.hpp"
#include "FileIterator.hpp"

#include "types.hpp"
#include "patterns.hpp"
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
  
public:
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

  std::list<std::string> getAvailableMetatags(void);

public: // configuration
  void setDirectory(const FilePath &directory);
  const FilePath getDirectory(void) const;
  sigc::signal<void, FilePath> SignalDirectoryChanged;
  
  void setFileFilter(const UnicodeString &filter);
  const UnicodeString getFileFilter(void);
  sigc::signal<void, UnicodeString> SignalFileFilterChanged;

  void setSortExpression(const UnicodeString &filter);
  const UnicodeString getSortExpression(void);
  sigc::signal<void, UnicodeString> SignalSortExpressionChanged;

  void setMetatagExpression(const UnicodeString &expression);
  void setMetatagExpression(Metatag::Expression::Pointer expression);
  Metatag::Expression::Pointer getMetatagExpression(void);
  sigc::signal<void, const Metatag::Expression::Pointer> SignalMetatagExpressionChanged;

  boost::property_tree::ptree& getConfigTree(void);

public: // ranaming process
  void resetState(void);
  void startRename(void);
  void stopRename(void);
  
  sigc::signal<void> SignalRenameStarted;
  sigc::signal<void> SignalRenameStopped;
  sigc::signal<void, MruException &> SignalRenameError;
  sigc::signal<void, FilePath, FilePath> SignalFilenameChange;

  FileIterator::Pointer getDirectoryIterator(void);

  FilePath generateNewFilepath(const FileIterator::Pointer file_iterator);

private:
  void loadDefaultConfiguration(void);
  void saveConfiguration(void);
  void applyConfiguration(void);
  template<typename PluginType>
  void loadAllModulesIn(const FilePath &directory, typename PluginType::DynamicManager::Pointer plugin_manager);
  std::list<FilePath> listFilesInDirectory(const FilePath &directory);

private:
  boost::property_tree::ptree reg;
  UiPlugin::Pointer ui_plugin;
  InputPlugin::Pointer input_plugin;
  OutputPlugin::Pointer output_plugin;

  InputPlugin::DynamicManager::Pointer input_plugin_manager;
  OutputPlugin::DynamicManager::Pointer output_plugin_manager;
  UiPlugin::DynamicManager::Pointer ui_plugin_manager;
  MetatagPlugin::DynamicManager::Pointer metatag_plugin_manager;

  Metatag::Expression::Pointer metatag_expression;
  Metatag::Expression::Pointer sorting_expression;
  UnicodeString file_filter_glob;

  class RegexFilterPredicate : public FilteringFileIterator::FilterPredicate {
  public:
    typedef boost::shared_ptr<RegexFilterPredicate> Pointer;
    static Pointer create(const UnicodeString &glob_expression);
    RegexFilterPredicate(const UnicodeString &glob_expression);
    bool operator()(const FilePath &path);
  private:
    UErrorCode matcher_status;
    icu::RegexMatcher matcher;
  };
  RegexFilterPredicate::Pointer file_filter_predicate;
};

} /* namespace mru */

#endif /* CORE_HPP */

