#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"
#include "patterns.hpp"
#include <sigc++/trackable.h>

namespace mru
{


// forward declarations:
class UiPlugin;
class OutputPlugin;

class Core : public singleton<Core> {
public:
  typedef Core self_type;
public: //slots/signals
  
public:
  Core(void);
  ~Core(void);

  registry get_registry(void);

  int start(int a_argc, char **a_argv);

  void prepare_registry(void);
  void load_configuration(void);
  void save_configuration(void);
  void parse_command_line(int a_argc, char **a_argv);
  void load_modules(void);

  //set_source_directory(const filepath_type &a_directory);


protected:
  UiPlugin *m_ui;
  OutputPlugin *m_out_driver;
};

} /* namespace mru */

#endif /* CORE_HPP */

