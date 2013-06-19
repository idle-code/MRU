#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"
#include "patterns.hpp"
#include "FileIterator.hpp"
#include <sigc++/sigc++.h>
#include <boost/filesystem.hpp>

namespace mru
{

namespace bfs = boost::filesystem;

// forward declarations:
class UiPlugin;
class OutputPlugin;

class MruCore : public singleton<MruCore> {
public:
  typedef MruCore self_type;
public: //slots/signals
  //error occured
  //rename started
  //rename ended
  //modules loaded
  //configuration changed
  
public:
  MruCore(void);
  ~MruCore(void);

  registry& get_registry(void);

  int start(int a_argc, char **a_argv);
  void parse_command_line(int a_argc, char **a_argv);

  bool load_configuration(const filepath_type &a_file =filepath_type());
  bool save_configuration(const filepath_type &a_file =filepath_type());

  bool set_base_directory(const filepath_type &a_directory);
  const filepath_type& get_base_directory(void) const;
  sigc::signal<void, filepath_type> base_directory_changed;
  
  bool set_current_directory(const filepath_type &a_directory);
  const filepath_type& get_current_directory(void) const;
  sigc::signal<void, filepath_type> current_directory_changed;

  bool set_file_filter(const UnicodeString &a_filter);
  const UnicodeString& get_file_filter(void);
  sigc::signal<void, UnicodeString> filter_changed;

  bool set_metatag_expression(const UnicodeString &a_expression);
  const UnicodeString& get_metatag_expression(void); //really needed?
  sigc::signal<void, UnicodeString, int, int> expression_error_occured; //(expression, position, length, type)

  FileIterator get_directory_iterator(const filepath_type &a_directory);

  void start_rename(void);
  sigc::signal<void> rename_started;
  void pause_rename(void);
  sigc::signal<void> rename_paused;
  void stop_rename(void);
  sigc::signal<void> rename_stopped;

  sigc::signal<void> error_occured;
  sigc::signal<void, filepath_type, filepath_type> filename_changed; //(filename_before, filename_after)

  UiPlugin* get_ui_plugin(void);
  OutputPlugin* get_output_plugin(void);

protected:
  UiPlugin *m_ui;
  OutputPlugin *m_out_driver;

  filepath_type m_base_directory;
  filepath_type m_current_directory;
protected:
  int load_modules_directory(const filepath_type &a_directory, bool a_recursively =true);
  int load_default_modules(void);
  
};

} /* namespace mru */

#endif /* CORE_HPP */

