#ifndef WXWIDGETSUI_HPP
#define WXWIDGETSUI_HPP

#include "MruCore.hpp"
#include "plugins/UiPlugin.hpp"
#include <wx/app.h>

namespace mru
{

namespace detail
{

class wxWidgetsUiApp : public wxApp {
public:
  wxWidgetsUiApp(MruCore *a_mru_core);
  ~wxWidgetsUiApp(void);

  bool OnInit(void);
  //int OnRun(void);
private:
  MruCore* m_core;
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

