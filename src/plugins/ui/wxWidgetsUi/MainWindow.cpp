#include "MainWindow.hpp"

#undef NDEBUG_L
#include <debug_l.h>
#include <wx/treectrl.h>
#include <wx/spinctrl.h>
#include <wx/event.h>
#include "types.hpp"

namespace mru
{

MainWindow::MainWindow(Core *a_mru_core)
  : wxFrame(NULL, wxID_ANY, wxT("MRU - Multifile Renaming Utility"), wxPoint(-1, -1), wxSize(840, 520)), m_core(a_mru_core)
{

  wxColour red, green, blue, dark_blue;
  red.Set(wxT("#ff0000"));
  green.Set(wxT("#00ff00"));
  blue.Set(wxT("#b0b0ff"));
  dark_blue.Set(wxT("#0000ff"));

  wxBoxSizer *vsizer = new wxBoxSizer(wxVERTICAL);

  wxStaticBoxSizer *tree_sizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Plugins"));
  { // plugins tree:
    wxTreeCtrl *tree = new wxTreeCtrl(this, wxID_ANY);
    tree->SetBackgroundColour(green);
    tree_sizer->Add(tree, 1, wxEXPAND, 0);
  }

  // expression, source directory and other settings:
  wxStaticBoxSizer *settings_sizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Settings"));
  { // source directory:
    wxBoxSizer *source_directory_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *source_directory_label = new wxStaticText(this, wxID_ANY, wxT("Source directory:"));
    m_source_directory_textctrl = new wxTextCtrl(this, wxID_ANY, wxT("/"));
    m_source_directory_button = new wxButton(this, wxID_ANY, wxT("..."));
    m_source_directory_button->SetMinSize(wxSize(30, 20));
    wxStaticText *source_directory_mask_label = new wxStaticText(this, wxID_ANY, wxT("File mask:"));
    m_source_directory_mask_textctrl = new wxTextCtrl(this, wxID_ANY, wxT("*"));

    source_directory_sizer->Add(source_directory_label,         0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    source_directory_sizer->Add(m_source_directory_textctrl,      1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT, 0);
    source_directory_sizer->Add(m_source_directory_button,        0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 3);
    source_directory_sizer->Add(source_directory_mask_label,    0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxRIGHT, 3);
    source_directory_sizer->Add(m_source_directory_mask_textctrl, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxLEFT | wxRIGHT, 3);

    settings_sizer->Add(source_directory_sizer, 0, wxEXPAND, 0);

    Connect(m_source_directory_textctrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainWindow::OnSourceDirectoryTextCtrlChange));
    Connect(m_source_directory_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnSourceDirectoryButtonClick));
  }

  settings_sizer->Add(-1, 3);

  { // metatag expression:
    wxBoxSizer *metatag_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *metatag_label = new wxStaticText(this, wxID_ANY, wxT("Expression:"));
    wxTextCtrl *metatag_textctrl = new wxTextCtrl(this, wxID_ANY, wxT("%NAME()"));
    wxButton *metatag_load_template_button = new wxButton(this, wxID_ANY, wxT("Load template"));
    metatag_load_template_button->SetMinSize(wxSize(-1, 20));

    metatag_sizer->Add(metatag_label, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    metatag_sizer->Add(metatag_textctrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
    metatag_sizer->Add(metatag_load_template_button, 0, wxALIGN_CENTER_VERTICAL, 0);

    settings_sizer->Add(metatag_sizer, 0, wxEXPAND, 0);

    Connect(metatag_load_template_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnMetatagLoadTemplateButtonClick));
    Connect(metatag_textctrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainWindow::OnMetatagTextCtrlChange));
  }

  settings_sizer->Add(-1, 3);

  // top horizontal sizer:
  wxBoxSizer *top_hsizer = new wxBoxSizer(wxHORIZONTAL);
  top_hsizer->Add(tree_sizer, 1, wxEXPAND, 0);
  top_hsizer->Add(settings_sizer, 3, wxEXPAND | wxLEFT, 5);
  vsizer->Add(top_hsizer, 0, wxEXPAND | wxALL, 5);

  { // file list:
    wxListCtrl *file_listctrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES);
    wxListItem before_column;
    before_column.SetId(0);
    before_column.SetText(wxT("Before"));
    before_column.SetWidth(200);
    file_listctrl->InsertColumn(0, before_column);
    wxListItem after_column;
    after_column.SetId(1);
    after_column.SetText(wxT("After"));
    after_column.SetWidth(200);
    file_listctrl->InsertColumn(1, after_column);
    vsizer->Add(file_listctrl, 2, wxEXPAND | wxLEFT | wxRIGHT, 5);
  }
  
  { // file list settings and buttons:
    wxBoxSizer *bottom_hsizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *preview_size_label = new wxStaticText(this, wxID_ANY, wxT("Files in preview:"));
    wxSpinCtrl *preview_size_spinctrl = new wxSpinCtrl(this, wxID_ANY);
    preview_size_spinctrl->SetRange(1, 1000);
    preview_size_spinctrl->SetValue(10);
    wxCheckBox *auto_preview_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Automatically update preview list"));
    wxButton *preview_button = new wxButton(this, wxID_ANY, wxT("Preview"));
    wxButton *start_button = new wxButton(this, wxID_ANY, wxT("Start"));

    bottom_hsizer->Add(preview_size_label,    0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    bottom_hsizer->Add(preview_size_spinctrl, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxRIGHT, 3);
    bottom_hsizer->AddStretchSpacer();
    bottom_hsizer->Add(auto_preview_checkbox, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxRIGHT, 3);
    bottom_hsizer->Add(preview_button,        0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxRIGHT, 3);
    bottom_hsizer->Add(start_button,          0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 0);
    
    vsizer->Add(bottom_hsizer, 0, wxEXPAND | wxALL, 5);

    Connect(preview_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnPreviewButtonClick));
    Connect(start_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStartButtonClick));
  }

  SetSizer(vsizer);

  //Connect(this->GetId(), wxEVT_CLOSE_WINDOW, wxCommandEventHandler(MainWindow::OnClose));
}

MainWindow::~MainWindow(void)
{ }

/* ------------------------------------------------------------------------- */

void
MainWindow::fill_filelist(void)
{
  FO("MainWindow::fill_filelist(void)");

  
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

}

void
MainWindow::OnSourceDirectoryButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnSourceDirectoryButtonClick(wxCommandEvent &a_evt)");
  fill_filelist();
}

void
MainWindow::OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnMetatagLoadTemplateButtonClick(wxCommandEvent &a_evt)");

}

void
MainWindow::OnMetatagTextCtrlChange(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnMetatagTextCtrlChange(wxCommandEvent &a_evt)");

}

void
MainWindow::OnPreviewButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnPreviewButtonClick(wxCommandEvent &a_evt)");

}

void
MainWindow::OnStartButtonClick(wxCommandEvent &a_evt)
{
  FO("MainWindow::OnStartButtonClick(wxCommandEvent &a_evt)");
  data_tree::print_tree( m_core->get_registry() );

}

} /* namespace mru */

