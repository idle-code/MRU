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
  : UiPlugin(static_implementation_name())
{ }

wxWidgetsUi::~wxWidgetsUi(void)
{ }

int
wxWidgetsUi::start(int a_argc, char *a_argv[])
{
  FO("wxWidgetsUi::start(int a_argc, char *a_argv[])");
  
  detail::wxWidgetsUiApp *app = new detail::wxWidgetsUiApp(core());
  wxApp::SetInstance(app);
  int result = wxEntry(a_argc, a_argv);
  VAL(result);
  delete app;

  return result;
}

/* ------------------------------------------------------------------------- */

namespace detail
{

wxWidgetsUiApp::wxWidgetsUiApp(MruCore *a_mru_core)
  : wxApp(), m_core(a_mru_core)
{
  int result = XInitThreads();
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

EXPORT_START
  EXPORT_PLUGIN(mru::wxWidgetsUi)
EXPORT_END

