#include "MainWindow.hpp"
#include "glue_extension.hpp"

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

MainWindow::MainWindow(MruCore *mru_core)
  : wxFrame(NULL, wxID_ANY, wxT("MRU - Multifile Renaming Utility"), wxPoint(-1, -1), wxSize(840, 520)),
    m_core(mru_core), m_preview_size(25) //TODO: replace by reg["ui.preview_size"] or something
{
  FO("MainWindow::MainWindow(MruCore *mru_core)");
  m_instance = this;
  if(m_core == NULL) {
    ERR("There is no valid MRU MruCore class instance passed to GUI");
    return;
  }

  wxFont main_font = this->GetFont(); 
  main_font.SetPointSize(12);
  this->SetFont(main_font);

  wxColour red, green, blue, dark_blue;
  red.Set(wxT("#cf0000"));
  green.Set(wxT("#00cf00"));
  blue.Set(wxT("#b0b0ff"));
  dark_blue.Set(wxT("#0000ff"));

  wxBoxSizer *vsizer = new wxBoxSizer(wxVERTICAL);

  wxStaticBoxSizer *tree_sizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Plugins"));
  { // metatag list:
    //TODO: move m_metatag_listbox to class (as property)
    m_metatag_listbox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE | wxLB_ALWAYS_SB | wxLB_SORT);
    //m_metatag_listbox->SetBackgroundColour(green);
    tree_sizer->Add(m_metatag_listbox, 1, wxEXPAND, 0);

    std::list<std::string> plugins = m_core->getAvailableMetatags();
    std::list<wxString> wx_plugins; //CHECK: useless?
    for(std::list<std::string>::iterator i = plugins.begin(); i != plugins.end(); ++i) {
      wxString metatag_name = glue_cast<wxString>(*i);
      m_metatag_listbox->InsertItems(1, &metatag_name, 0);
    }

    Connect(m_metatag_listbox->GetId(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(MainWindow::OnMetatagListClick));
  }

  // expression, source directory and other settings:
  wxStaticBoxSizer *settings_sizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Settings"));
  { // source directory:
    wxBoxSizer *source_directory_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *source_directory_label = new wxStaticText(this, wxID_ANY, wxT("Source directory:"));
    m_source_directory_textctrl = new wxTextCtrl(this, wxID_ANY, glue_cast<wxString>(m_core->getDirectory()));
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

    m_work_on_directories_checkbox->SetValue(m_core->getConfigTree().get<bool>("run.work_on.directories"));
    m_include_directories_checkbox->SetValue(m_core->getConfigTree().get<bool>("run.include.directories"));
    m_include_files_checkbox->SetValue(m_core->getConfigTree().get<bool>("run.include.files"));


    settings_panel_sizer->Add(m_work_on_directories_checkbox, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 3);
    settings_panel_sizer->Add(m_reset_on_directory_change, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    settings_panel_sizer2->Add(m_include_directories_checkbox, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 3);
    settings_panel_sizer2->Add(m_include_files_checkbox, 0, wxALIGN_CENTER_VERTICAL, 3);

    settings_sizer->Add(settings_panel_sizer, 0, wxEXPAND, 0);
    settings_sizer->Add(settings_panel_sizer2, 0, wxEXPAND, 0);

    m_work_on_directories_checkbox->SetValue(m_core->getConfigTree().get<bool>("run.work_on.directories"));
    m_include_directories_checkbox->SetValue(m_core->getConfigTree().get<bool>("run.include.directories"));
    m_include_files_checkbox->SetValue(m_core->getConfigTree().get<bool>("run.include.files"));
    m_reset_on_directory_change->SetValue(m_core->getConfigTree().get<bool>("run.reset_on_directory_change"));

    Connect(m_work_on_directories_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnWorkOnDirectoriesCheckboxClick));
    Connect(m_include_directories_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnIncludeDirectoriesCheckboxClick));
    Connect(m_include_files_checkbox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnIncludeFilesCheckboxClick));
    Connect(m_reset_on_directory_change->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainWindow::OnResetOnDirectoryChangeCheckboxClick));
  }

  settings_sizer->Add(-1, 3);

  { // sorting expression:
    wxBoxSizer *sorting_expression_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *sorting_expression_label = new wxStaticText(this, wxID_ANY, wxT("Sort expression:"));
    m_sorting_expression_textctrl = new wxTextCtrl(this, wxID_ANY, glue_cast<wxString>(m_core->getSortExpression()->text()));
    wxTextAttr style = m_sorting_expression_textctrl->GetDefaultStyle();
    //wxFont font = style.GetFont();
    //font.SetPointSize(20);
    //m_sorting_expression_textctrl->SetFont(font);

    m_asc_sort_radio_button = new wxRadioButton(this, wxID_ANY, wxT("Ascending"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    m_desc_sort_radio_button = new wxRadioButton(this, wxID_ANY, wxT("Descending"));

    sorting_expression_sizer->Add(sorting_expression_label, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    sorting_expression_sizer->Add(m_sorting_expression_textctrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    sorting_expression_sizer->Add(m_asc_sort_radio_button, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    sorting_expression_sizer->Add(m_desc_sort_radio_button, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);

    settings_sizer->Add(sorting_expression_sizer, 0, wxEXPAND, 0);

    Connect(m_sorting_expression_textctrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainWindow::OnSortingExpressionTextCtrlChange));
    Connect(m_asc_sort_radio_button->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(MainWindow::OnSortingOrderRadioButtonChange));
    Connect(m_desc_sort_radio_button->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(MainWindow::OnSortingOrderRadioButtonChange));
  }

  { // metatag expression:
    wxBoxSizer *metatag_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *metatag_label = new wxStaticText(this, wxID_ANY, wxT("Rename expression:"));
    m_metatag_textctrl = new wxTextCtrl(this, wxID_ANY, glue_cast<wxString>(m_core->getMetatagExpression()->text()));
    wxTextAttr style = m_metatag_textctrl->GetDefaultStyle();
    //wxFont font = style.GetFont();
    //font.SetPointSize(20);
    //m_metatag_textctrl->SetFont(font);

    m_metatag_load_template_button = new wxButton(this, wxID_ANY, wxT("Load template"));
    m_metatag_load_template_button->Hide();
    m_metatag_load_template_button->SetMinSize(wxSize(-1, 20));

    metatag_sizer->Add(metatag_label, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    metatag_sizer->Add(m_metatag_textctrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);

    settings_sizer->Add(metatag_sizer, 0, wxEXPAND, 0);

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
  FILE_RENAMED_ID = wxNewId();
  RENAME_STOPPED_ID = wxNewId();
  RENAME_ERROR_ID = wxNewId();

  SignalRenameStartedConnection = m_core->SignalRenameStarted.connect(sigc::mem_fun(this, &MainWindow::OnRenameStartedEvent));
  SignalRenameStoppedConnection = m_core->SignalRenameStopped.connect(sigc::mem_fun(this, &MainWindow::OnRenameStoppedEvent));
  SignalRenameErrorConnection = m_core->SignalRenameError.connect(sigc::mem_fun(this, &MainWindow::OnRenameErrorEvent));
  SignalFilenameChangeConnection =  m_core->SignalFilenameChange.connect(sigc::mem_fun(this, &MainWindow::OnFileRenamedEvent));

  Connect(wxID_ANY, RENAME_STARTED_ID ,wxCommandEventHandler(MainWindow::OnRenameStarted));
  Connect(wxID_ANY, FILE_RENAMED_ID ,wxCommandEventHandler(MainWindow::OnFileRenamed));
  Connect(wxID_ANY, RENAME_STOPPED_ID ,wxCommandEventHandler(MainWindow::OnRenameStopped));
  Connect(wxID_ANY, RENAME_ERROR_ID ,wxCommandEventHandler(MainWindow::OnRenameError));

  SetSizer(vsizer);

  Connect(this->GetId(), wxEVT_CLOSE_WINDOW, wxCommandEventHandler(MainWindow::OnClose));
}

MainWindow::~MainWindow(void)
{
  SignalRenameStartedConnection.disconnect();
  SignalRenameStoppedConnection.disconnect();
  SignalRenameErrorConnection.disconnect();
  SignalFilenameChangeConnection.disconnect();
}

/* ------------------------------------------------------------------------- */

void
MainWindow::fill_filelist(void)
{
  FO("MainWindow::fill_filelist(void)");

  m_file_listctrl->ClearAll();
  FileIterator::Pointer dir_iter = m_core->getDirectoryIterator();
  if (!dir_iter)
    return;

  // generate(preserve) column widths:
  int before_column_width = m_file_listctrl->GetColumnWidth(0);
  int after_column_width = m_file_listctrl->GetColumnWidth(1);
  wxSize file_list_size = m_file_listctrl->GetClientSize();
  if(before_column_width == 0)
    before_column_width = file_list_size.GetWidth() / 2;
  if(after_column_width == 0)
    after_column_width = file_list_size.GetWidth() / 2;

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

  // fill list:
  for(int i = 0; (i < m_preview_size || m_preview_size == 0) && !dir_iter->atEnd(); ++i, dir_iter->next())
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

    try {
      if(m_core->getConfigTree().get<bool>("run.work_on.directories"))
        before_entry.SetText(glue_cast<wxString>(bfs::make_relative(m_core->getDirectory(), glue_cast<FilePath>(dir_iter->getCurrent()))));
      else
        before_entry.SetText(glue_cast<wxString>(dir_iter->getCurrent().filename()));
    } catch (std::exception &me) {
      //ERR(me.getMessage());
      ERR(me.what());
    }

    if(m_file_listctrl->InsertItem(before_entry) == -1) {
      WARN("InsertItem failed");
    }

    wxListItem after_entry;
    after_entry.SetId(i);
    after_entry.SetColumn(1);

    try {
      FilePath new_path = m_core->generateNewFilepath(dir_iter);
      if(m_core->getConfigTree().get<bool>("run.work_on.directories"))
        new_path = bfs::make_relative(m_core->getDirectory(), new_path);
      else if(!bfs::is_directory(new_path))
        new_path = new_path.filename();
      else
        new_path = FilePath();
      after_entry.SetText(glue_cast<wxString>(new_path));
    } catch(MetatagPlugin::Exception &me) {
      after_entry.SetBackgroundColour(wxColour(210, 0, 0));
      after_entry.SetText(glue_cast<wxString>(me.getMessage()));
    } catch (MruException &e) {
      ERR(e.getMessage());
    } catch (std::exception &e) {
      ERR("Other exception" << e.what());
    }

    if(!m_file_listctrl->SetItem(after_entry)) {
      WARN("SetItem failed");
    }
  }
}

void
MainWindow::OnFileListSize(wxSizeEvent &evt)
{
  //FO("MainWindow::OnFileListSize(wxCommandEvent &evt)");
  //VAL(this);
  //VAL(this->m_file_listctrl);
  if(m_file_listctrl != NULL && m_file_listctrl->GetColumnCount() == 2) {
    m_file_listctrl->SetColumnWidth(0, evt.GetSize().GetWidth() / 2);
    m_file_listctrl->SetColumnWidth(1, evt.GetSize().GetWidth() / 2);
  }
  evt.Skip();
}

void
MainWindow::OnFileListClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnFileListClick(wxCommandEvent &evt)");

}

/* ------------------------------------------------------------------------- */

void
MainWindow::OnMetatagListClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnMetatagListClick(wxCommandEvent &evt)");
  VAL(m_metatag_textctrl->GetInsertionPoint());
  wxString metatag = wxT("%") + evt.GetString() + wxT("()");
  m_metatag_textctrl->WriteText(metatag);
}

/* ------------------------------------------------------------------------- */

void
MainWindow::OnClose(wxCommandEvent &evt)
{
  FO("MainWindow::OnClose(wxCommandEvent &evt)");

  evt.Skip();
}

void
MainWindow::OnSourceDirectoryTextCtrlChange(wxCommandEvent &evt)
{
  FO("MainWindow::OnSourceDirectoryTextCtrlChange(wxCommandEvent &evt)");
  try {
    m_core->setDirectory(glue_cast<FilePath>(m_source_directory_textctrl->GetValue()));
  } catch(...) { //FIXME: add proper exception type
    ERR(glue_cast<std::string>(m_source_directory_mask_textctrl->GetValue()) << " is not valid directory path");
  }
  //m_source_directory_textctrl->SetValue(glue_cast<wxString>(m_core->get_base_directory()));
  //fill_filelist();
}

void
MainWindow::OnSourceDirectoryButtonClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnSourceDirectoryButtonClick(wxCommandEvent &evt)");
  wxDirDialog dir_dialog(NULL, wxT("Choose directory"), glue_cast<wxString>(m_core->getDirectory()), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
  if(wxID_OK == dir_dialog.ShowModal()) {
    try {
      m_core->setDirectory(glue_cast<FilePath>(dir_dialog.GetPath()));
      m_source_directory_textctrl->SetValue(glue_cast<wxString>(m_core->getDirectory()));
      fill_filelist();
    } catch(...) { //FIXME: add proper exception type
      ERR(glue_cast<std::string>(dir_dialog.GetPath()) << " is not valid directory path");
    }
  }
}

void
MainWindow::OnWorkOnDirectoriesCheckboxClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnWorkOnDirectoriesCheckboxClick(wxCommandEvent &evt)");
  m_core->getConfigTree().put<bool>("run.work_on.directories", m_work_on_directories_checkbox->GetValue());
  fill_filelist();
}

void
MainWindow::OnIncludeDirectoriesCheckboxClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnIncludeDirectoriesCheckboxClick(wxCommandEvent &evt)");
  m_core->getConfigTree().put<bool>("run.include.directories", m_include_directories_checkbox->GetValue());
  fill_filelist();
}

void
MainWindow::OnIncludeFilesCheckboxClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnIncludeFilesCheckboxClick(wxCommandEvent &evt)");
  m_core->getConfigTree().put<bool>("run.include.files", m_include_files_checkbox->GetValue());
  fill_filelist();
}

void
MainWindow::OnResetOnDirectoryChangeCheckboxClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnResetOnDirectoryChangeCheckboxClick(wxCommandEvent &evt)");
  m_core->getConfigTree().put<bool>("run.reset_on_directory_change", m_reset_on_directory_change->GetValue());
  fill_filelist();
}

void
MainWindow::OnSourceDirectoryMaskTextCtrlChange(wxCommandEvent &evt)
{
  FO("MainWindow::OnSourceDirectoryMaskTextCtrlChange(wxCommandEvent &evt)");
  try {
  m_core->setFileFilter(glue_cast<UnicodeString>(m_source_directory_mask_textctrl->GetValue()));
  } catch (MruException &me) {
    ERR(me.getMessage());
  }
  fill_filelist();
}

static UnicodeString last_good_sorting_expression;
void
MainWindow::OnSortingExpressionTextCtrlChange(wxCommandEvent &evt)
{
  FO("MainWindow::OnSortingExpressionTextCtrlChange(wxCommandEvent &evt)");
  try {
    last_good_sorting_expression = m_core->getSortExpression()->text();  
    m_core->setSortExpression(glue_cast<UnicodeString>(m_sorting_expression_textctrl->GetValue()));
    m_sorting_expression_textctrl->SetBackgroundColour(wxColour(255, 255, 255));
  } catch(Metatag::Expression::Exception &mee) {
    m_sorting_expression_textctrl->SetBackgroundColour(wxColour(250, 80, 0));
    WARN("MetatagExpressionException: " << glue_cast<std::string>(mee.getMessage()));
    m_core->setSortExpression(last_good_sorting_expression);
  } catch(Metatag::MetatagBase::Exception &me) {
    m_sorting_expression_textctrl->SetBackgroundColour(wxColour(250, 250, 0));
    WARN("MetatagException: " << glue_cast<std::string>(me.getMessage()));
    m_core->setSortExpression(last_good_sorting_expression);
  }

  if(m_auto_preview_checkbox->GetValue()) {
    fill_filelist();
  }
}

void
MainWindow::OnSortingOrderRadioButtonChange(wxCommandEvent &evt)
{
  if (m_asc_sort_radio_button->GetValue())
    m_core->getConfigTree().put<std::string>("run.sort.direction", "ascending");
  else
    m_core->getConfigTree().put<std::string>("run.sort.direction", "descending");
  m_core->setSortExpression(glue_cast<UnicodeString>(m_sorting_expression_textctrl->GetValue()));
  fill_filelist();
}

static UnicodeString last_good_expression;
void
MainWindow::OnMetatagTextCtrlChange(wxCommandEvent &evt)
{
  FO("MainWindow::OnMetatagTextCtrlChange(wxCommandEvent &evt)");
  try {
    last_good_expression = m_core->getMetatagExpression()->text();  
    m_core->setMetatagExpression(glue_cast<UnicodeString>(m_metatag_textctrl->GetValue()));
    m_metatag_textctrl->SetBackgroundColour(wxColour(255, 255, 255));
  } catch(Metatag::Expression::Exception &mee) {
    m_metatag_textctrl->SetBackgroundColour(wxColour(250, 80, 0));
    WARN("MetatagExpressionException: " << glue_cast<std::string>(mee.getMessage()));
    m_core->setMetatagExpression(last_good_expression);
  } catch(Metatag::MetatagBase::Exception &me) {
    m_metatag_textctrl->SetBackgroundColour(wxColour(250, 250, 0));
    WARN("MetatagException: " << glue_cast<std::string>(me.getMessage()));
    m_core->setMetatagExpression(last_good_expression);
  }

  if(m_auto_preview_checkbox->GetValue()) {
    fill_filelist();
  }
}

void
MainWindow::OnAutoPreviewCheckboxClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnAutoPreviewCheckboxClick(wxCommandEvent &evt)");
  m_preview_button->Enable(!m_auto_preview_checkbox->GetValue());
  //wxCommandEvent evt;
  OnPreviewButtonClick(evt);
}

void
MainWindow::OnPreviewButtonClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnPreviewButtonClick(wxCommandEvent &evt)");
  try {
    //m_core->setMetatagExpression(glue_cast<UnicodeString>(m_metatag_textctrl->GetValue())); //FIXME
    fill_filelist();
  } catch(Metatag::Expression::Exception &mee) {
    wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(mee.getMessage()), wxT("Metatag expression error"), wxOK);
    error_messagebox->ShowModal();
    //if(mee.range().first >= 0)
    //  m_metatag_textctrl->SetSelection(mee.range().first, mee.range().first + mee.range().second);
  } catch(MetatagPlugin::Exception &me) {
    wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(me.getMessage()), wxT("Metatag error"), wxOK);
    error_messagebox->ShowModal();
  }
}

void
MainWindow::OnStartButtonClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnStartButtonClick(wxCommandEvent &evt)");
  m_core->startRename();
}

void
MainWindow::OnStopButtonClick(wxCommandEvent &evt)
{
  FO("MainWindow::OnStopButtonClick(wxCommandEvent &evt)");
  m_core->stopRename();
}

void
MainWindow::OnPreviewSizeSpinCtrlSpin(wxCommandEvent &evt)
{
  m_preview_size = m_preview_size_spinctrl->GetValue();
  fill_filelist();
}

void
MainWindow::OnRenameStartedEvent(void)
{
  FO("MainWindow::OnRenameStartedEvent(void)");
  //wxCommandEvent evt(RENAME_STARTED_ID, wxID_ANY); 
  //wxEvtHandler *window = MainWindow::get_instance();
  //wxPostEvent(window, evt);
  wxCommandEvent evt(RENAME_STARTED_ID, wxID_ANY); 
  ProcessEvent(evt);
}

void
MainWindow::OnRenameStarted(wxCommandEvent &event)
{
  FO("MainWindow::OnRenameStarted(wxCommandEvent &event)");
  bool enabled = false;
  m_include_directories_checkbox->Enable(enabled);
  m_include_files_checkbox->Enable(enabled);
  m_work_on_directories_checkbox->Enable(enabled);
  m_metatag_listbox->Enable(enabled);
  m_sorting_expression_textctrl->Enable(enabled);
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
  if (!Disconnect(m_start_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED)) {
    WARN("Failed to disconnect button events");
  }
  Connect(m_start_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStopButtonClick));
}

void
MainWindow::OnRenameStoppedEvent(void)
{
  FO("MainWindow::OnRenameStoppedEvent(void)");
  wxCommandEvent evt(RENAME_STOPPED_ID, wxID_ANY); 
  ProcessEvent(evt);
}
void
MainWindow::OnRenameStopped(wxCommandEvent &event)
{
  FO("MainWindow::OnRenameStopped(wxCommandEvent &event)");
  bool enabled = true;
  m_include_directories_checkbox->Enable(enabled);
  m_include_files_checkbox->Enable(enabled);
  m_work_on_directories_checkbox->Enable(enabled);
  m_metatag_listbox->Enable(enabled);
  m_sorting_expression_textctrl->Enable(enabled);
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
  if (!Disconnect(m_start_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED)) {
    WARN("Failed to disconnect button events");
  }
  Connect(m_start_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStartButtonClick));

  fill_filelist();
}

void
MainWindow::OnFileRenamedEvent(FilePath before, FilePath after)
{
  FO("MainWindow::OnFileRenamedEvent(FilePath before, FilePath after)");
  wxCommandEvent evt(FILE_RENAMED_ID, wxID_ANY); 
  ProcessEvent(evt);
  VAL(before);
  VAL(after);
}
void
//MainWindow::OnFileRenamed(FilePath before, FilePath after)
MainWindow::OnFileRenamed(wxCommandEvent &event)
{
  FO("MainWindow::OnFileRenamed(wxCommandEvent &event)");
}

void
MainWindow::OnRenameErrorEvent(const MruException &exception)
{
  FO("MainWindow::OnRenameErrorEvent(void)");
  wxCommandEvent evt(RENAME_ERROR_ID, wxID_ANY); 
  evt.SetString(glue_cast<wxString>(exception.getMessage()));
  ProcessEvent(evt);
}
void
MainWindow::OnRenameError(wxCommandEvent &event)
{
  FO("OnRenameError(const UnicodeString &message)");
  wxMessageDialog *error_messagebox = new wxMessageDialog(this, glue_cast<wxString>(event.GetString()) + wxT("\n\nContinue rename?"), wxT("Rename error occured"), wxYES_NO | wxNO_DEFAULT);
  if(wxID_NO == error_messagebox->ShowModal()) {
    m_core->stopRename();
  }
}

} /* namespace mru */

