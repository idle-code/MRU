#include "MainWindow.hpp"

#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

MainWindow::MainWindow(void)
  : wxFrame(NULL, -1, wxT("MRU - Multifile Renaming Utility"), wxPoint(100, 100), wxSize(450, 340))
{ }

MainWindow::~MainWindow(void)
{ }

bool
MainWindow::OnInit(void)
{
  FO("MainWindow::OnInit(void)");



  return true;
}

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
  //EVT_MENU(ID_SelectDirectory, MyFrame::select_directory)
END_EVENT_TABLE()

} /* namespace mru */

