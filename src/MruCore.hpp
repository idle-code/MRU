#ifndef CORE_HPP
#define CORE_HPP

#include "plugins/UiPlugin.hpp"
#include "plugins/InputPlugin.hpp"
#include "plugins/OutputPlugin.hpp"
#include "plugins/TagPlugin.hpp"

#include "types.hpp"
#include "patterns.hpp"
#include "FileIterator.hpp"
#include <sigc++/sigc++.h>
#include <boost/filesystem.hpp>
#include "metatag/expression.hpp"
#include <pthread.h>

namespace mru
{

namespace bfs = boost::filesystem;

// forward declarations:
class UiPlugin;
class OutputPlugin;

class MruCore : public singleton<MruCore> {
public:
  typedef MruCore self_type;
  
public: // generic methods
  MruCore(void);
  ~MruCore(void);

  registry& getRegistry(void);

  int start(int a_argc, char **a_argv);

  bool loadConfiguration(const FilePath &a_file = FilePath()); 
  bool saveConfiguration(const FilePath &a_file = FilePath()); 

  UiPlugin* getUiPlugin(void);
  OutputPlugin* getOutputPlugin(void);

  std::list<std::string> getAvailableMetatags(void);

public: // program state/configuration
  void setDirectory(const FilePath &a_directory);
  const FilePath& getDirectory(void) const;
  sigc::signal<void, FilePath> SignalDirectoryChanged;
  
  void setFileFilter(const UnicodeString &a_filter);
  const UnicodeString& getFileFilter(void);
  sigc::signal<void, UnicodeString> SignalFileFilterChanged;

  void setMetatagExpression(const UnicodeString &a_expression);
  UnicodeString getMetatagExpression(void);
  sigc::signal<void, const UnicodeString &> SignalMetatagExpressionChanged;

  FileIterator::Pointer getIterator(void);
  FilePath generateNewFilepath(const FileIterator *a_iterator);

public: // ranaming process
  void resetState(void);
  void startRename(void);
  sigc::signal<void> SignalRenameStarted;
  void stopRename(void);
  sigc::signal<void> SignalRenameStopped;

  sigc::signal<void, const UnicodeString &> SignalMetatagException;
  sigc::signal<void, const UnicodeString &> SignalOutputException;
  sigc::signal<void, FilePath, FilePath> SignalFilenameChange;

private:
  UiPlugin *m_ui;
  InputPlugin *m_input;
  OutputPlugin *m_output;
  FilePath m_directory;
  MetatagExpression m_metatag_expression;

  friend void* worker_thread_main(void *a_core_pointer);
  pthread_t m_worker_thread;

  int loadModulesDirectory(const FilePath &a_directory, bool a_recursively =true);
  int loadDefaultModules(void);
  int loadMetatags(void);
  bool m_bindings_outdated;
  void bindMetatags(void);
};

} /* namespace mru */

#endif /* CORE_HPP */

