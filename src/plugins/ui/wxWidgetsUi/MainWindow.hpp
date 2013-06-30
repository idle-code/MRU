#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "MruCore.hpp"

namespace mru
{

class MainWindow : public wxFrame {
public:
  typedef MainWindow self_type;
public:
  MainWindow(MruCore *a_mru_core);
  ~MainWindow(void);

  void fill_filelist(void);
  
private:
  void OnClose(wxCommandEvent &a_evt);
private:
  // metatag list
  wxListBox *m_metatag_listbox;
  void OnMetatagListClick(wxCommandEvent &a_evt); 
  // metatag expression
  wxTextCtrl *m_metatag_textctrl;
  wxButton *m_metatag_load_template_button;

  // source directory
  filepath_type m_source_directory;
  wxTextCtrl *m_source_directory_textctrl;
  void OnSourceDirectoryTextCtrlChange(wxCommandEvent &a_evt);

  wxButton *m_source_directory_button;
  void OnSourceDirectoryButtonClick(wxCommandEvent &a_evt);

  // top panel
  wxCheckBox *m_work_on_directories_checkbox;
  void OnWorkOnDirectoriesCheckboxClick(wxCommandEvent &a_evt);
  wxCheckBox *m_include_directories_checkbox;
  void OnIncludeDirectoriesCheckboxClick(wxCommandEvent &a_evt);
  wxCheckBox *m_include_files_checkbox;
  void OnIncludeFilesCheckboxClick(wxCommandEvent &a_evt);

  // source directory mask
  wxTextCtrl *m_source_directory_mask_textctrl;

  void OnMetatagTextCtrlChange(wxCommandEvent &a_evt);
  void OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt);

  // bottom panel
  wxCheckBox *m_auto_preview_checkbox;
  void OnAutoPreviewCheckboxClick(wxCommandEvent &a_evt);
  wxButton *m_preview_button;
  void OnPreviewButtonClick(wxCommandEvent &a_evt);
  void OnStartButtonClick(wxCommandEvent &a_evt);
  wxSpinCtrl *m_preview_size_spinctrl;
  void OnPreviewSizeSpinCtrlSpin(wxCommandEvent &a_evt);

  // file list
  wxListCtrl *m_file_listctrl;
  void OnFileListSize(wxSizeEvent &a_evt);
  void OnFileListClick(wxCommandEvent &a_evt);
private:
  MruCore* m_core;
  int m_preview_size;
};

} /* namespace mru */

#endif /* MAINWINDOW_HPP */

