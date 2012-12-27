#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>

namespace mru
{

class MainWindow : public wxFrame {
public:
  typedef MainWindow self_type;
public:
  MainWindow(void);
  ~MainWindow(void);

  DECLARE_EVENT_TABLE()
};

} /* namespace mru */

#endif /* MAINWINDOW_HPP */

