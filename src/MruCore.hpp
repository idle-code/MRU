#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"
#include "patterns.hpp"
#include "FileIterator.hpp"
#include <sigc++/sigc++.h>
#include <boost/filesystem.hpp>
#include "metatag/expression.hpp"

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

  void include_directories(bool enable);
  bool include_directories(void) const;
  void include_filenames(bool enable);
  bool include_filenames(void) const;
  void work_on_directories(bool enable);
  bool work_on_directories(void) const;


  int start(int a_argc, char **a_argv);
  void parse_command_line(int a_argc, char **a_argv);

  bool load_configuration(const filepath_type &a_file =filepath_type());
  bool save_configuration(const filepath_type &a_file =filepath_type());

  void set_base_directory(const filepath_type &a_directory);
  const filepath_type& get_base_directory(void) const;
  sigc::signal<void, filepath_type> base_directory_changed;
  
  void set_current_directory(const filepath_type &a_directory);
  const filepath_type& get_current_directory(void) const;
  sigc::signal<void, filepath_type> current_directory_changed;

  void set_file_filter(const UnicodeString &a_filter);
  const UnicodeString& get_file_filter(void);
  sigc::signal<void, UnicodeString> filter_changed;

  void set_metatag_expression(const UnicodeString &a_expression);
  UnicodeString get_metatag_expression(void); //really needed?
  sigc::signal<void, UnicodeString, int, int> expression_error_occured; //(expression, position, length, type)

  FileIterator get_directory_iterator(void);
  UnicodeString generate_filepath(const FileIterator &a_iterator);

  void reset_state(void);

  void start_rename(void);
  sigc::signal<void> rename_started;
  void pause_rename(void);
  sigc::signal<void> rename_paused;
  void stop_rename(void);
  sigc::signal<void> rename_stopped;

  sigc::signal<void> rename_error_occured;
  sigc::signal<void, filepath_type, filepath_type> filename_changed; //(filename_before, filename_after)

  UiPlugin* get_ui_plugin(void);
  OutputPlugin* get_output_plugin(void);

  std::list<UnicodeString> get_available_metatags(void);

private:
  UiPlugin *m_ui;
  OutputPlugin *m_out_driver;

  filepath_type m_base_directory;
  filepath_type m_current_directory;

  MetatagExpression m_metatag_expression;

  bool m_include_directories;
  bool m_include_filenames;
  bool m_work_on_directories;

  int load_modules_directory(const filepath_type &a_directory, bool a_recursively =true);
  int load_default_modules(void);
  int load_tags(void);
  bool m_bindings_outdated;
  void bind_metatags(void);
};

} /* namespace mru */

#endif /* CORE_HPP */

