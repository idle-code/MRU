#ifndef TEXTUI_HPP
#define TEXTUI_HPP

#include <plugins/UiPlugin.hpp>

namespace mru
{

class TextUi : public UiPlugin {
public:
  typedef TextUi self_type;
public:
  PLUGIN_NAME("TextUi");
  TextUi(void);
  ~TextUi(void);

  int start(int a_argc, char *a_argv[]);

};

} /* namespace mru */

#endif /* TEXTUI_HPP */

