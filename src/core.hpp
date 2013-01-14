#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"
#include "patterns.hpp"
#include <sigc++/trackable.h>
#include <boost/filesystem.hpp>

namespace mru
{

namespace bfs = boost::filesystem;

// forward declarations:
class UiPlugin;
class OutputPlugin;

class Core : public singleton<Core> {
public:
  typedef Core self_type;
public: //slots/signals
  //error occured
  //rename started
  //rename ended
  //modules loaded
  //configuration changed
public:
  Core(void);
  ~Core(void);

  registry get_registry(void);

  int start(int a_argc, char **a_argv);
  void parse_command_line(int a_argc, char **a_argv);

  void prepare_registry(void);
  bool load_configuration(const filepath_type &a_file =filepath_type());
  bool save_configuration(const filepath_type &a_file =filepath_type());
  int load_modules_directory(const filepath_type &a_directory, bool a_recursively =true);
  int load_default_modules(void);

  bool set_base_directory(const filepath_type &a_directory);
  const filepath_type& get_base_directory(void) const;

  bool set_file_filter(const UnicodeString &a_filter);
  const UnicodeString& get_file_filter(void);

  bool set_metatag_expression(const UnicodeString &a_expression);
  const UnicodeString& get_metatag_expression(void); //really needed?

  bool start_rename(void);
  bool pause_rename(void);
  bool stop_rename(void);

  bfs::directory_iterator get_directory_iterator(const filepath_type &a_directory);


  UiPlugin* get_ui_plugin(void);
  OutputPlugin* get_output_plugin(void);

protected:
  UiPlugin *m_ui;
  OutputPlugin *m_out_driver;

  filepath_type m_base_directory;
  filepath_type m_current_directory;
  
};

} /* namespace mru */

#endif /* CORE_HPP */

