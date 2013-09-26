#include "wxWidgetsUi.hpp"
#undef NDEBUG_L
#include <debug_l.h>
#include "MainWindow.hpp"
#include <X11/Xlib.h>
#include <wx/app.h>
#include <wx/init.h>

namespace mru
{

wxWidgetsUi::wxWidgetsUi(void)
{ }

wxWidgetsUi::~wxWidgetsUi(void)
{ }

int
wxWidgetsUi::start(int a_argc, char *a_argv[])
{
  FO("wxWidgetsUi::start(int a_argc, char *a_argv[])");
  
  try {
    detail::wxWidgetsUiApp *app = new detail::wxWidgetsUiApp(getCore());
    wxApp::SetInstance(app);
    int result = wxEntry(a_argc, a_argv);
    VAL(result);
    delete app;
    return result;
  } catch (MruException &e) {
    ERR(e.getMessage());
    return -1;
  }
}

/* ------------------------------------------------------------------------- */

namespace detail
{

wxWidgetsUiApp::wxWidgetsUiApp(MruCore *a_mru_core)
  : wxApp(), m_core(a_mru_core)
{
  assert(m_core);
  int result = XInitThreads();
  //FIXME?: check result?
}

wxWidgetsUiApp::~wxWidgetsUiApp(void)
{ }

bool
wxWidgetsUiApp::OnInit(void)
{
  FO("wxWidgetsUiApp::OnInit(void)");

  MainWindow *main_window = new MainWindow(m_core);
  main_window->Show(true);
  SetTopWindow(main_window);

  return true;
}

//int
//wxWidgetsUiApp::OnRun(void)
//{
//  FO("wxWidgetsUiApp::OnRun(void)");
//  return 0;
//}

}

} /* namespace mru */

EXPORT_PLUGIN_FACTORY(UiPlugin, mru::wxWidgetsUi)


