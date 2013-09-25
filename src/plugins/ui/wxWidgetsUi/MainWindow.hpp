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
  static MainWindow* get_instance(void);
public:
  MainWindow(MruCore *mru_core);
  ~MainWindow(void);

  void fill_filelist(void);
  
private:
  static MainWindow *m_instance;
  void OnClose(wxCommandEvent &evt);
private:
  // metatag list
  wxListBox *m_metatag_listbox;
  void OnMetatagListClick(wxCommandEvent &evt); 
  // metatag expression
  wxTextCtrl *m_metatag_textctrl;
  void OnMetatagTextCtrlChange(wxCommandEvent &evt);
  // template
  wxButton *m_metatag_load_template_button;
  void OnMetatagLoadTemplateButtonClick(wxCommandEvent &evt);

  // source directory
  FilePath m_source_directory;
  wxTextCtrl *m_source_directory_textctrl;
  void OnSourceDirectoryTextCtrlChange(wxCommandEvent &evt);

  wxButton *m_source_directory_button;
  void OnSourceDirectoryButtonClick(wxCommandEvent &evt);
  
  // source directory mask
  wxTextCtrl *m_source_directory_mask_textctrl;
  void OnSourceDirectoryMaskTextCtrlChange(wxCommandEvent &evt);

  // top checkboxes
  wxCheckBox *m_work_on_directories_checkbox;
  void OnWorkOnDirectoriesCheckboxClick(wxCommandEvent &evt);
  wxCheckBox *m_include_directories_checkbox;
  void OnIncludeDirectoriesCheckboxClick(wxCommandEvent &evt);
  wxCheckBox *m_include_files_checkbox;
  void OnIncludeFilesCheckboxClick(wxCommandEvent &evt);
  wxCheckBox *m_reset_on_directory_change;
  void OnResetOnDirectoryChangeCheckboxClick(wxCommandEvent &evt);

  // bottom panel
  wxCheckBox *m_auto_preview_checkbox;
  void OnAutoPreviewCheckboxClick(wxCommandEvent &evt);
  wxButton *m_preview_button;
  void OnPreviewButtonClick(wxCommandEvent &evt);
  wxButton *m_start_button;
  void OnStartButtonClick(wxCommandEvent &evt);
  wxSpinCtrl *m_preview_size_spinctrl;
  void OnPreviewSizeSpinCtrlSpin(wxCommandEvent &evt);

  void OnRenameStartedEvent(void);
  void OnRenameStoppedEvent(void);
  void OnRenameStarted(wxCommandEvent &evt);
  void OnRenameStopped(wxCommandEvent &evt);
  void OnFileRenamed(FilePath before, FilePath after);
  void OnRenameErrorEvent(const MruException &exception);
  void OnRenameError(wxCommandEvent &evt);

  // file list
  wxListCtrl *m_file_listctrl;
  void OnFileListSize(wxSizeEvent &evt);
  void OnFileListClick(wxCommandEvent &evt);
private:
  MruCore* m_core;
  int m_preview_size;
  int RENAME_STARTED_ID;
  int RENAME_STOPPED_ID;
  int RENAME_ERROR_ID;

  sigc::connection SignalRenameStartedConnection;
  sigc::connection SignalRenameStoppedConnection;
  sigc::connection SignalRenameErrorConnection;
  sigc::connection SignalFilenameChangeConnection;
};

} /* namespace mru */

#endif /* MAINWINDOW_HPP */

