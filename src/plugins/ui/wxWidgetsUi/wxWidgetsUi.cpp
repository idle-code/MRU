#include "wxWidgetsUi.hpp"
#undef NDEBUG_L
#include <debug_l.h>
#include "MainWindow.hpp"
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
  
  //TODO: start main window
  
  detail::wxWidgetsUiApp *app = new detail::wxWidgetsUiApp;
  wxApp::SetInstance(app);
  int result = wxEntry(a_argc, a_argv);
  delete app;

  return result;
}

/* ------------------------------------------------------------------------- */

namespace detail
{

wxWidgetsUiApp::wxWidgetsUiApp(void)
  : wxApp()
{ }

wxWidgetsUiApp::~wxWidgetsUiApp(void)
{ }

bool
wxWidgetsUiApp::OnInit(void)
{
  FO("wxWidgetsUiApp::OnInit(void)");
  MainWindow *main_window = new MainWindow();
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

