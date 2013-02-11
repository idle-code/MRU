#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>
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
  
  filepath_type m_source_directory;
  wxTextCtrl *m_source_directory_textctrl;
  void OnSourceDirectoryTextCtrlChange(wxCommandEvent &a_evt);

  wxButton *m_source_directory_button;
  void OnSourceDirectoryButtonClick(wxCommandEvent &a_evt);

  wxTextCtrl *m_source_directory_mask_textctrl;

  void OnMetatagTextCtrlChange(wxCommandEvent &a_evt);
  void OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt);

  wxCheckBox *m_auto_preview_checkbox;
  void OnAutoPreviewCheckboxClick(wxCommandEvent &a_evt);
  wxButton *m_preview_button;
  void OnPreviewButtonClick(wxCommandEvent &a_evt);
  void OnStartButtonClick(wxCommandEvent &a_evt);
  wxSpinCtrl *m_preview_size_spinctrl;
  void OnPreviewSizeSpinCtrlSpin(wxCommandEvent &a_evt);

  wxListCtrl *m_file_listctrl;
private:
  Core* m_core;
  int m_preview_size;
};

} /* namespace mru */

#endif /* MAINWINDOW_HPP */

