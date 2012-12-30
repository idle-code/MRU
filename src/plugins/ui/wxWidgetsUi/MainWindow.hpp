#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>
#include <core.hpp>

namespace mru
{

class MainWindow : public wxFrame {
public:
  typedef MainWindow self_type;
public:
  MainWindow(Core *a_mru_core);
  ~MainWindow(void);

  void fill_filelist(void);
  
private:
  void OnClose(wxCommandEvent &a_evt);
  
  wxTextCtrl *m_source_directory_textctrl;
  void OnSourceDirectoryTextCtrlChange(wxCommandEvent &a_evt);
  wxButton *m_source_directory_button;
  void OnSourceDirectoryButtonClick(wxCommandEvent &a_evt);
  wxTextCtrl *m_source_directory_mask_textctrl;

  void OnMetatagTextCtrlChange(wxCommandEvent &a_evt);
  void OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt);

  void OnPreviewButtonClick(wxCommandEvent &a_evt);
  void OnStartButtonClick(wxCommandEvent &a_evt);

private:
  Core* m_core;
};

} /* namespace mru */

#endif /* MAINWINDOW_HPP */

