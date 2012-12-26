#ifndef WXWIDGETSUI_HPP
#define WXWIDGETSUI_HPP

#include <plugins/ui_plugin.hpp>
#include <wx/app.h>

namespace mru
{

namespace detail
{

class wxWidgetsUiApp : public wxApp {
public:
  wxWidgetsUiApp(void);
  ~wxWidgetsUiApp(void);

  bool OnInit(void);
  //int OnRun(void);
};

}

class wxWidgetsUi : public UiPlugin {
public:
  typedef wxWidgetsUi self_type;
public:
  PLUGIN_NAME("wxWidgetsUi")
  wxWidgetsUi(void);
  ~wxWidgetsUi(void);

  int start(int a_argc, char *a_argv[]);
};

} /* namespace mru */

#endif /* WXWIDGETSUI_HPP */

