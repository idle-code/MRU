#include "MainWindow.hpp"

#undef NDEBUG_L
#include <debug_l.h>
#include <wx/listbox.h>
#include <wx/dirdlg.h>
#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/colour.h>
#include "PathValidator.hpp"
#include "types.hpp"
#include "glue.hpp"
#include <make_relative_fix.hpp>

namespace mru
{

MainWindow *
MainWindow::m_instance = NULL;

MainWindow *
MainWindow::get_instance(void)
{
  return m_instance;
}

MainWindow::MainWindow(MruCore *a_mru_core)
  : wxFrame(NULL, wxID_ANY, wxT("MRU - Multifile Renaming Utility"), wxPoint(-1, -1), wxSize(840, 520)),
    m_core(a_mru_core), m_preview_size(25) //TODO: replace by reg["ui.preview_size"] or something
{
  FO("MainWindow::MainWindow(MruCore *a_mru_core)");
  m_instance = this;
  if(m_core == NULL) {
    ERR("There is no valid MRU MruCore class instance passed to GUI");
    return;
  }

  wxColour red, green, blue, dark_blue;
  red.Set(wxT("#ff0000"));
  green.Set(wxT("#00ff00"));
  blue.Set(wxT("#b0b0ff"));
  dark_blue.Set(wxT("#0000ff"));

  wxBoxSizer *vsizer = new wxBoxSizer(wxVERTICAL);

  wxStaticBoxSizer *tree_sizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Plugins"));
  { // metatag list:
    //TODO: move m_metatag_listbox to class (as property)
    m_metatag_listbox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE | wxLB_ALWAYS_SB | wxLB_SORT);
    //m_metatag_listbox->SetBackgroundColour(green);
    tree_sizer->Add(m_metatag_listbox, 1, wxEXPAND, 0);

    std::list<UnicodeString> plugins = m_core->get_available_metatags();
    std::list<wxString> wx_plugins;
    for(std::list<UnicodeString>::iterator i = plugins.begin(); i != plugins.end(); ++i) {
      wx_plugins.push_back(glue_cast<wxString>(*i));
      m_metatag_listbox->InsertItems(1, &wx_plugins.back(), 0);
    }

    Connect(m_metatag_listbox->GetId(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(MainWindow::OnMetatagListClick));
  }

  // expression, source directory and other settings:
  wxStaticBoxSizer *settings_sizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Settings"));
  { // source directory:
    wxBoxSizer *source_directory_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *source_directory_label = new wxStaticText(this, wxID_ANY, wxT("Source directory:"));
    m_source_directory_textctrl = new wxTextCtrl(this, wxID_ANY, glue_cast<wxString>(m_core->get_base_directory()));
    m_source_directory_textctrl->SetValidator(PathValidator(true, true, &m_source_directory));
    m_source_directory_button = new wxButton(this, wxID_ANY, wxT("..."));
    m_source_directory_button->SetMinSize(wxSize(30, 20));
    wxStaticText *source_directory_mask_label = new wxStaticText(this, wxID_ANY, wxT("File mask:"));
    m_source_directory_mask_textctrl = new wxTextCtrl(this, wxID_ANY, wxT(".*"));

    source_directory_sizer->Add(source_directory_label,           0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    source_directory_sizer->Add(m_source_directory_textctrl,      1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT, 0);
    source_directory_sizer->Add(m_source_directory_button,        0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 3);
    source_directory_sizer->Add(source_directory_mask_label,      0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxRIGHT, 3);
    source_directory_sizer->Add(m_source_directory_mask_textctrl, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxLEFT | wxRIGHT, 3);

    settings_sizer->Add(source_directory_sizer, 0, wxEXPAND, 0);

    Connect(m_source_directory_textctrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainWindow::OnSourceDirectoryTextCtrlChange));
    Connect(m_source_directory_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnSourceDirectoryButtonClick));
    Connect(m_source_directory_mask_textctrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainWindow::OnSourceDirectoryMaskTextCtrlChange));
  }

  { // top panel checkboxes
    wxBoxSizer *settings_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *settings_panel_sizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_work_on_directories_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Work on directories"));
    m_include_directories_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Include directories"));
    m_include_files_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Include files"));
    m_reset_on_directory_change = new wxCheckBox(this, wxID_ANY, wxT("Reset tags on directory change"));

    m_work_on_directories_checkbox->SetValue(m_core->work_on_directories());
    m_include_directories_checkbox->SetValue(m_core->include_directories());
    m_include_files_checkbox->SetValue(m_core->include_filenames());

    settings_panel_sizer->Add(m_work_on_directories_checkbox, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 3);
    settings_panel_sizer->Add(m_reset_on_directory_change, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    settings_panel_sizer2->Add(m_include_directories_checkbox, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 3);
    settings_panel_sizer2->Add(m_include_files_checkbox, 0, wxALIGN_CENTER_VERTICAL, 3);

    settings_sizer->Add(settings_panel_sizer, 0, wxEXPAND, 0);
    settings_sizer->Add(settings_panel_sizer2, 0, wxEXPAND, 0);

    m_work_on_directories_checkbox->SetValue(m_core->work_on_directories());
    m_include_directories_checkbox->SetValue(m_core->include_directories());
    m_include_files_checkbox->SetValue(m_core->include_filenames());
    m_reset_on_directory_change->SetValue(m_core->reset_on_directory_change());

    Connect(m_work_on_directories_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnWorkOnDirectoriesCheckboxClick));
    Connect(m_include_directories_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnIncludeDirectoriesCheckboxClick));
    Connect(m_include_files_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnIncludeFilesCheckboxClick));
    Connect(m_reset_on_directory_change->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnResetOnDirectoryChangeCheckboxClick));
  }

  settings_sizer->Add(-1, 3);

  { // metatag expression:
    wxBoxSizer *metatag_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *metatag_label = new wxStaticText(this, wxID_ANY, wxT("Expression:"));
    m_metatag_textctrl = new wxTextCtrl(this, wxID_ANY, glue_cast<wxString>(m_core->get_metatag_expression()));
    //wxTextAttr style = m_metatag_textctrl->GetDefaultStyle();
    //wxFont font = style.GetFont();
    //font.SetWeight(20);
    //style.SetFont(font);
    //m_metatag_textctrl->SetDefaultStyle(style);
    m_metatag_load_template_button = new wxButton(this, wxID_ANY, wxT("Load template"));
    m_metatag_load_template_button->Hide();
    m_metatag_load_template_button->SetMinSize(wxSize(-1, 20));

    metatag_sizer->Add(metatag_label, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    metatag_sizer->Add(m_metatag_textctrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    //metatag_sizer->Add(m_metatag_load_template_button, 0, wxALIGN_CENTER_VERTICAL, 0);

    settings_sizer->Add(metatag_sizer, 0, wxEXPAND, 0);

    Connect(m_metatag_load_template_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnMetatagLoadTemplateButtonClick));
    Connect(m_metatag_textctrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainWindow::OnMetatagTextCtrlChange));
  }

  settings_sizer->Add(-1, 3);

  // top horizontal sizer:
  wxBoxSizer *top_hsizer = new wxBoxSizer(wxHORIZONTAL);
  top_hsizer->Add(tree_sizer, 1, wxEXPAND, 0);
  top_hsizer->Add(settings_sizer, 3, wxEXPAND | wxLEFT, 5);
  vsizer->Add(top_hsizer, 0, wxEXPAND | wxALL, 5);

  { // file list:
    m_file_listctrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES);
    vsizer->Add(m_file_listctrl, 2, wxEXPAND | wxLEFT | wxRIGHT, 5);

    Connect(m_file_listctrl->GetId(), wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxCommandEventHandler(MainWindow::OnFileListClick));
    m_file_listctrl->Connect(wxEVT_SIZE, wxSizeEventHandler(MainWindow::OnFileListSize), NULL, this);
    //Connect(m_file_listctrl->GetId(), wxEVT_SIZE, wxSizeEventHandler(MainWindow::OnFileListSize));

    fill_filelist();
  }
  
  { // file list settings and buttons:
    wxBoxSizer *bottom_hsizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *preview_size_label = new wxStaticText(this, wxID_ANY, wxT("Files in preview:"));
    m_preview_size_spinctrl = new wxSpinCtrl(this, wxID_ANY);
    m_preview_size_spinctrl->SetRange(0, 1000);
    m_preview_size_spinctrl->SetValue(m_preview_size);
    m_auto_preview_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Automatically update preview list"));
    m_preview_button = new wxButton(this, wxID_ANY, wxT("Preview"));
    m_start_button = new wxButton(this, wxID_ANY, wxT("Start"));

    bottom_hsizer->Add(preview_size_label,      0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    bottom_hsizer->Add(m_preview_size_spinctrl, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    bottom_hsizer->AddStretchSpacer();
    bottom_hsizer->Add(m_auto_preview_checkbox, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxRIGHT, 3);
    bottom_hsizer->Add(m_preview_button,        0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxRIGHT, 3);
    bottom_hsizer->Add(m_start_button,            0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 0);
    
    vsizer->Add(bottom_hsizer, 0, wxEXPAND | wxALL, 5);

    Connect(m_auto_preview_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnAutoPreviewCheckboxClick));
    Connect(m_preview_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnPreviewButtonClick));
    Connect(m_start_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStartButtonClick));
    Connect(m_preview_size_spinctrl->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(MainWindow::OnPreviewSizeSpinCtrlSpin));
  }

  RENAME_STARTED_ID = wxNewId();
  RENAME_STOPPED_ID = wxNewId();
  RENAME_ERROR_ID = wxNewId();

  m_core->rename_started.connect(sigc::mem_fun(this, &MainWindow::OnRenameStartedEvent));
  m_core->rename_stopped.connect(sigc::mem_fun(this, &MainWindow::OnRenameStoppedEvent));
  m_core->rename_error_occured.connect(sigc::mem_fun(this, &MainWindow::OnRenameErrorEvent));
  m_core->filename_changed.connect(sigc::mem_fun(this, &MainWindow::OnFileRenamed));

  Connect(wxID_ANY, RENAME_STARTED_ID ,wxCommandEventHandler(MainWindow::OnRenameStarted));
  Connect(wxID_ANY, RENAME_STOPPED_ID ,wxCommandEventHandler(MainWindow::OnRenameStopped));
  //Connect(wxID_ANY, RENAME_ERROR_ID ,wxCommandEventHandler(MainWindow::OnRenameError));

  SetSizer(vsizer);

  Connect(this->GetId(), wxEVT_CLOSE_WINDOW, wxCommandEventHandler(MainWindow::OnClose));
}

MainWindow::~MainWindow(void)
{ }

/* ------------------------------------------------------------------------- */

void
MainWindow::fill_filelist(void)
{
  FO("MainWindow::fill_filelist(void)");

  FileIterator dir_iter = m_core->get_directory_iterator();
  FileIterator dir_end;

  // generate(preserve) column widths:
  int before_column_width = m_file_listctrl->GetColumnWidth(0);
  int after_column_width = m_file_listctrl->GetColumnWidth(1);
  wxSize file_list_size = m_file_listctrl->GetClientSize();
  if(before_column_width == 0)
    before_column_width = file_list_size.GetWidth() / 2;
  if(after_column_width == 0)
    after_column_width = file_list_size.GetWidth() / 2;

  m_file_listctrl->ClearAll();

  // set columns:
  wxListItem before_column;
  before_column.SetId(0);
  before_column.SetText(wxT("Before"));
  before_column.SetWidth(before_column_width);
  m_file_listctrl->InsertColumn(0, before_column);
  wxListItem after_column;
  after_column.SetId(1);
  after_column.SetText(wxT("After"));
  after_column.SetWidth(after_column_width);
  m_file_listctrl->InsertColumn(1, after_column);

  m_core->reset_state();
  // fill list:
  for(int i = 0; (i < m_preview_size || m_preview_size == 0) && dir_iter != dir_end; ++i, ++dir_iter)
  {
    //VAL(glue_cast<std::string>(dir_iter.base_filename()));
    //VAL(glue_cast<std::string>(dir_iter.base_directory()));
    //VAL(glue_cast<std::string>(dir_iter.directory()));
    //VAL(glue_cast<std::string>(dir_iter.filename()));
    //VAL(glue_cast<std::string>(dir_iter.bare_filename()));
    //MSG("----------------------");
    wxListItem before_entry;
    before_entry.SetId(i);
    before_entry.SetColumn(0);

    if(m_core->work_on_directories())
      before_entry.SetText(glue_cast<wxString>(dir_iter.filename()));
    else
      before_entry.SetText(glue_cast<wxString>(dir_iter.bare_filename()));

    if(m_file_listctrl->InsertItem(before_entry) == -1) {
      WARN("InsertItem failed");
    }

    wxListItem after_entry;
    after_entry.SetId(i);
    after_entry.SetColumn(1);

    //if(m_core->include_directories())
    try {
      filepath_type new_path = m_core->generate_filepath(dir_iter);
      if(m_core->work_on_directories())
        new_path = bfs::make_relative(glue_cast<filepath_type>(dir_iter.base_directory()), glue_cast<filepath_type>(new_path));
      else if(!bfs::is_directory(new_path))
        new_path = new_path.filename();
      else
        new_path = filepath_type();
      after_entry.SetText(glue_cast<wxString>(new_path));
    } catch(MetatagException &me) {
      after_entry.SetBackgroundColour(wxColour(210, 0, 0));
      after_entry.SetText(glue_cast<wxString>(me.message()));
    }

    if(!m_file_listctrl->SetItem(after_entry)) {
      WARN("SetItem failed");
    }
    //m_file_listctrl->InsertItem(i, wxT("TEST"));
  }
}

void
MainWindow::OnFileListSize(wxSizeEvent &a_evt)
{
  //FO("MainWindow::OnFileListSize(wxCommandEvent &a_evt)");
  //VAL(this);
  //VAL(this->m_file_listctrl);
  if(m_file_listctrl != NULL && m_file_listctrl->GetColumnCount() == 2) {
    m_file_listctrl->SetColumnWidth(0, a_evt.GetSize().GetWidth() / 2);
    m_file_listctrl->SetColumnWidth(1, a_evt.GetSize().GetWidth() / 2);
  }
  a_evt.Skip();
}

void
MainWindow::OnFileListClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnFileListClick(wxCommandEvent &a_evt)");

}

/* ------------------------------------------------------------------------- */

void
MainWindow::OnMetatagListClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnMetatagListClick(wxCommandEvent &a_evt)");
  VAL(m_metatag_textctrl->GetInsertionPoint());
  wxString metatag = wxT("%") + a_evt.GetString() + wxT("()");
  m_metatag_textctrl->WriteText(metatag);
}

/* ------------------------------------------------------------------------- */

void
MainWindow::OnClose(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnClose(wxCommandEvent &a_evt)");

  a_evt.Skip();
}

void
MainWindow::OnSourceDirectoryTextCtrlChange(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnSourceDirectoryTextCtrlChange(wxCommandEvent &a_evt)");
  try {
    m_core->set_base_directory(glue_cast<filepath_type>(m_source_directory_textctrl->GetValue()));
  } catch(...) { //FIXME: add proper exception type
    ERR(glue_cast<std::string>(m_source_directory_mask_textctrl->GetValue()) << " is not valid directory path");
  }
  //m_source_directory_textctrl->SetValue(glue_cast<wxString>(m_core->get_base_directory()));
  //fill_filelist();
}

void
MainWindow::OnSourceDirectoryButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnSourceDirectoryButtonClick(wxCommandEvent &a_evt)");
  wxDirDialog dir_dialog(NULL, wxT("Choose directory"), glue_cast<wxString>(m_core->get_base_directory()), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
  if(wxID_OK == dir_dialog.ShowModal()) {
    try {
      m_core->set_base_directory(glue_cast<filepath_type>(dir_dialog.GetPath()));
      m_source_directory_textctrl->SetValue(glue_cast<wxString>(m_core->get_base_directory()));
      fill_filelist();
    } catch(...) { //FIXME: add proper exception type
      ERR(glue_cast<std::string>(dir_dialog.GetPath()) << " is not valid directory path");
    }
  }
}

void
MainWindow::OnWorkOnDirectoriesCheckboxClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnWorkOnDirectoriesCheckboxClick(wxCommandEvent &a_evt)");
  m_core->work_on_directories(m_work_on_directories_checkbox->GetValue());
  fill_filelist();
}

void
MainWindow::OnIncludeDirectoriesCheckboxClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnIncludeDirectoriesCheckboxClick(wxCommandEvent &a_evt)");
  m_core->include_directories(m_include_directories_checkbox->GetValue());
  fill_filelist();
}

void
MainWindow::OnIncludeFilesCheckboxClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnIncludeFilesCheckboxClick(wxCommandEvent &a_evt)");
  m_core->include_filenames(m_include_files_checkbox->GetValue());
  fill_filelist();
}

void
MainWindow::OnResetOnDirectoryChangeCheckboxClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnResetOnDirectoryChangeCheckboxClick(wxCommandEvent &a_evt)");
  m_core->reset_on_directory_change(m_reset_on_directory_change->GetValue());
  fill_filelist();
}

void
MainWindow::OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt)");

}

void
MainWindow::OnSourceDirectoryMaskTextCtrlChange(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnSourceDirectoryMaskTextCtrlChange(wxCommandEvent &a_evt)");
  m_core->set_file_filter(glue_cast<UnicodeString>(m_source_directory_mask_textctrl->GetValue()));
  fill_filelist();
}

static UnicodeString last_good_expression;
void
MainWindow::OnMetatagTextCtrlChange(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnMetatagTextCtrlChange(wxCommandEvent &a_evt)");
  if(m_auto_preview_checkbox->GetValue()) {
    try {
      m_core->set_metatag_expression(glue_cast<UnicodeString>(m_metatag_textctrl->GetValue()));
      fill_filelist();
      last_good_expression = m_core->get_metatag_expression();  
      m_metatag_textctrl->SetBackgroundColour(wxColour(255, 255, 255));
    } catch(MetatagExpressionException &mee) {
      m_metatag_textctrl->SetBackgroundColour(wxColour(250, 50, 0));
      WARN("MetatagExpressionException: " << glue_cast<std::string>(mee.message()));
      m_core->set_metatag_expression(last_good_expression);
      fill_filelist();
    } catch(MetatagException &me) {
      m_metatag_textctrl->SetBackgroundColour(wxColour(250, 250, 0));
      WARN("MetatagException: " << glue_cast<std::string>(me.message()));
      m_core->set_metatag_expression(last_good_expression);
      fill_filelist();
    }
  }
}

void
MainWindow::OnAutoPreviewCheckboxClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnAutoPreviewCheckboxClick(wxCommandEvent &a_evt)");
  m_preview_button->Enable(!m_auto_preview_checkbox->GetValue());
  wxCommandEvent evt;
  OnPreviewButtonClick(evt);
}

void
MainWindow::OnPreviewButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnPreviewButtonClick(wxCommandEvent &a_evt)");
  try {
    m_core->set_metatag_expression(glue_cast<UnicodeString>(m_metatag_textctrl->GetValue()));
    fill_filelist();
  } catch(MetatagExpressionException &mee) {
    wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(mee.message()), wxT("Metatag expression error"), wxOK);
    error_messagebox->ShowModal();
    if(mee.range().first >= 0)
      m_metatag_textctrl->SetSelection(mee.range().first, mee.range().first + mee.range().second);
  } catch(MetatagException &me) {
    wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(me.message()), wxT("Metatag error"), wxOK);
    error_messagebox->ShowModal();
  }
}

void
MainWindow::OnStartButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnStartButtonClick(wxCommandEvent &a_evt)");
  switch(m_core->get_worker_state()) {
    case MruCore::started:
      m_core->stop_rename();
      //m_
      break;
    case MruCore::paused:
      break;
    case MruCore::stopped:
      m_core->start_rename();
      break;
  }
}

void
MainWindow::OnPreviewSizeSpinCtrlSpin(wxCommandEvent &a_evt)
{
  m_preview_size = m_preview_size_spinctrl->GetValue();
  fill_filelist();
}

void
MainWindow::OnRenameStartedEvent(void)
{
  FO("MainWindow::OnRenameStartedEvent(void)");
  wxCommandEvent evt(RENAME_STARTED_ID, wxID_ANY); 
  wxEvtHandler *window = MainWindow::get_instance();
  VAL(this);
  VAL(MainWindow::get_instance());
  wxPostEvent(window, evt);
}

void
MainWindow::OnRenameStarted(wxCommandEvent &a_event)
{
  FO("MainWindow::OnRenameStarted(wxCommandEvent &a_event)");
  bool enabled = false;
  m_include_directories_checkbox->Enable(enabled);
  m_include_files_checkbox->Enable(enabled);
  m_work_on_directories_checkbox->Enable(enabled);
  m_metatag_listbox->Enable(enabled);
  m_metatag_textctrl->Enable(enabled);
  m_metatag_load_template_button->Enable(enabled);
  m_source_directory_button->Enable(enabled);
  m_source_directory_mask_textctrl->Enable(enabled);
  m_source_directory_textctrl->Enable(enabled);
  m_auto_preview_checkbox->Enable(enabled);
  m_preview_button->Enable(enabled);
  m_preview_size_spinctrl->Enable(enabled);
  m_reset_on_directory_change->Enable(enabled);

  m_start_button->SetLabel(wxT("Stop"));
}

void
MainWindow::OnRenameStoppedEvent(void)
{
  FO("MainWindow::OnRenameStoppedEvent(void)");
  wxCommandEvent evt(RENAME_STOPPED_ID, wxID_ANY); 
  wxEvtHandler *window = MainWindow::get_instance();
  wxPostEvent(window, evt);
}

void
MainWindow::OnRenameStopped(wxCommandEvent &a_event)
{
  FO("MainWindow::OnRenameStopped(wxCommandEvent &a_event)");
  bool enabled = true;
  m_include_directories_checkbox->Enable(enabled);
  m_include_files_checkbox->Enable(enabled);
  m_work_on_directories_checkbox->Enable(enabled);
  m_metatag_listbox->Enable(enabled);
  m_metatag_textctrl->Enable(enabled);
  m_metatag_load_template_button->Enable(enabled);
  m_source_directory_button->Enable(enabled);
  m_source_directory_mask_textctrl->Enable(enabled);
  m_source_directory_textctrl->Enable(enabled);
  m_auto_preview_checkbox->Enable(enabled);
  m_preview_button->Enable(!m_auto_preview_checkbox->GetValue());
  m_preview_size_spinctrl->Enable(enabled);
  m_reset_on_directory_change->Enable(enabled);

  m_start_button->SetLabel(wxT("Start"));

  fill_filelist();
}

void
MainWindow::OnFileRenamed(filepath_type a_before, filepath_type a_after)
{
  FO("OnFileRenamed(filepath_type a_before, filepath_type a_after)");
  
}

void
MainWindow::OnRenameErrorEvent(const UnicodeString &a_message)
{
  FO("MainWindow::OnRenameErrorEvent(void)");
  //wxCommandEvent evt(RENAME_ERROR_ID, wxID_ANY); 
  //evt.SetString(glue_cast<wxString>(a_message));
  //wxEvtHandler *window = MainWindow::get_instance();
  //wxPostEvent(window, evt);
  wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(a_message) + wxT("\n\nContinue rename?"), wxT("Rename error occured"), wxYES_NO | wxNO_DEFAULT);
  if(wxID_NO == error_messagebox->ShowModal()) {
    m_core->stop_rename();
  }
}

//void
//MainWindow::OnRenameError(wxCommandEvent &a_event)
//{
//  FO("OnRenameError(const UnicodeString &a_message)");
//  wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(a_event.GetString()) + wxT("\n\nContinue rename?"), wxT("Rename error occured"), wxYES_NO | wxNO_DEFAULT);
//  if(wxID_NO == error_messagebox->ShowModal()) {
//    m_core->stop_rename();
//  }
//}

} /* namespace mru */

