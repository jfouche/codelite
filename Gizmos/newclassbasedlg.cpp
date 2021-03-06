//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "newclassbasedlg.h"


// Declare the bitmap loading function
extern void wxC3999InitBitmapResources();

static bool bBitmapLoaded = false;


NewClassBaseDlg::NewClassBaseDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC3999InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);
    
    wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(  0, 4, 0, 0);
    fgSizer1->SetFlexibleDirection( wxBOTH );
    fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    fgSizer1->AddGrowableCol(1);
    
    bSizer1->Add(fgSizer1, 0, wxALL|wxEXPAND, 5);
    
    m_staticText1 = new wxStaticText(this, wxID_ANY, _("Class Name:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textClassName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(400,-1), 0);
    m_textClassName->SetToolTip(_("The class name"));
    m_textClassName->SetFocus();
    
    fgSizer1->Add(m_textClassName, 0, wxALL|wxEXPAND, 5);
    
    m_staticText9 = new wxStaticText(this, wxID_ANY, _("*"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_staticText9->SetForegroundColour(wxColour(wxT("rgb(255,0,0)")));
    wxFont m_staticText9Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText9Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText9->SetFont(m_staticText9Font);
    
    fgSizer1->Add(m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    m_staticTextNamespace = new wxStaticText(this, wxID_ANY, _("Namespace:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticTextNamespace, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlNamespace = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlNamespace->SetToolTip(_("Place this class inside a namespace"));
    
    fgSizer1->Add(m_textCtrlNamespace, 0, wxALL|wxEXPAND, 5);
    
    m_buttonBrowseNamespaces = new wxButton(this, wxID_ANY, _("Browse..."), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_buttonBrowseNamespaces, 0, wxALL, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    m_staticText6 = new wxStaticText(this, wxID_ANY, _("Block Guard:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlBlockGuard = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlBlockGuard->SetToolTip(_("Set block guard to prevent multiple file inclusion. If left empty, the class name is used"));
    
    fgSizer1->Add(m_textCtrlBlockGuard, 0, wxALL|wxEXPAND, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    m_staticText4 = new wxStaticText(this, wxID_ANY, _("Select Virtual Directory:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlVD = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), wxTE_READONLY);
    m_textCtrlVD->SetToolTip(_("The new class needs to be put somewhere. Select which of the project's virtual folders to use."));
    
    fgSizer1->Add(m_textCtrlVD, 0, wxALL|wxEXPAND, 5);
    
    m_buttonSelectVD = new wxButton(this, wxID_ANY, _("Browse..."), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_buttonSelectVD, 0, wxALL, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    m_staticText2 = new wxStaticText(this, wxID_ANY, _("Generated File(s) Path:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlGenFilePath = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlGenFilePath->SetToolTip(_("Where on the filesystem should the new class's files be put? This will normally be the directory corresponding to the Virtual Directory; but you can enter an alternative directory here if you wish."));
    
    fgSizer1->Add(m_textCtrlGenFilePath, 1, wxALL|wxEXPAND, 5);
    
    m_buttonBrowseFolder = new wxButton(this, wxID_ANY, _("Browse..."), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_buttonBrowseFolder, 0, wxALL, 5);
    
    wxBoxSizer* bSizer8 = new wxBoxSizer(wxVERTICAL);
    
    bSizer1->Add(bSizer8, 0, wxALL|wxEXPAND, 5);
    
    m_staticText8 = new wxStaticText(this, wxID_ANY, _("Generated File:"), wxDefaultPosition, wxSize(-1, -1), 0);
    wxFont m_staticText8Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText8Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText8->SetFont(m_staticText8Font);
    
    bSizer8->Add(m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    m_checkBoxUseUnderscores = new wxCheckBox(this, wxID_ANY, _("Use underscores to separate filename words (see tooltip) "), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxUseUnderscores->SetValue(false);
    m_checkBoxUseUnderscores->SetToolTip(_("If the class name is FooBarBaz, call the files foo_bar_baz.cpp etc instead of foobarbaz.cpp"));
    
    bSizer8->Add(m_checkBoxUseUnderscores, 0, wxALL, 5);
    
    m_checkBoxInline = new wxCheckBox(this, wxID_ANY, _("Inline class"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxInline->SetValue(false);
    m_checkBoxInline->SetToolTip(_("Put both the declaration and the implementation in the header file"));
    
    bSizer8->Add(m_checkBoxInline, 0, wxALL, 5);
    
    m_checkBoxHpp = new wxCheckBox(this, wxID_ANY, _("Create .hpp instead of .h"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxHpp->SetValue(false);
    m_checkBoxHpp->SetToolTip(_("If checked, the generated header file will be foo.hpp instead of foo.h"));
    
    bSizer8->Add(m_checkBoxHpp, 0, wxALL, 5);
    
    m_textCtrlFileName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlFileName->SetToolTip(_("This is the base-name for the file(s) that will be generated. If the new class is called Foo, by default the files will be foo.cpp and foo.h. If you'd prefer different names, type the base-name here."));
    
    bSizer8->Add(m_textCtrlFileName, 1, wxALL|wxEXPAND, 5);
    
    m_collPane2 = new wxCollapsiblePane(this, wxID_ANY, _("Advanced"), wxDefaultPosition, wxSize(-1,-1), wxCP_DEFAULT_STYLE);
    
    bSizer1->Add(m_collPane2, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* boxSizer6 = new wxBoxSizer(wxVERTICAL);
    m_collPane2->GetPane()->SetSizer(boxSizer6);
    
    m_staticText7 = new wxStaticText(m_collPane2->GetPane(), wxID_ANY, _("Inherits:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    boxSizer6->Add(m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    wxBoxSizer* bSizer15 = new wxBoxSizer(wxHORIZONTAL);
    
    boxSizer6->Add(bSizer15, 1, wxALL|wxEXPAND, 5);
    
    m_listCtrl1 = new wxListCtrl(m_collPane2->GetPane(), wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxLC_VRULES|wxLC_HRULES|wxLC_REPORT);
    
    bSizer15->Add(m_listCtrl1, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer16 = new wxBoxSizer(wxVERTICAL);
    
    bSizer15->Add(bSizer16, 0, wxEXPAND, 5);
    
    m_buttonAddInheritance = new wxButton(m_collPane2->GetPane(), wxID_ANY, _("Add..."), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAddInheritance->SetToolTip(_("Click to add a class from which to derive"));
    
    bSizer16->Add(m_buttonAddInheritance, 0, wxALL, 5);
    
    m_buttonDelInheritance = new wxButton(m_collPane2->GetPane(), wxID_ANY, _("Delete"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer16->Add(m_buttonDelInheritance, 0, wxALL, 5);
    
    wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(  0, 2, 0, 0);
    fgSizer2->SetFlexibleDirection( wxBOTH );
    fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    fgSizer2->AddGrowableCol(0);
    fgSizer2->AddGrowableCol(1);
    
    boxSizer6->Add(fgSizer2, 0, wxALL|wxEXPAND, 5);
    
    m_checkBoxCopyable = new wxCheckBox(m_collPane2->GetPane(), wxID_ANY, _("Declare this class non-copyable"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxCopyable->SetValue(false);
    
    fgSizer2->Add(m_checkBoxCopyable, 0, wxALL, 5);
    
    m_checkBoxImplVirtual = new wxCheckBox(m_collPane2->GetPane(), wxID_ANY, _("Implement all virtual functions"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxImplVirtual->SetValue(false);
    
    fgSizer2->Add(m_checkBoxImplVirtual, 0, wxALL, 5);
    
    m_checkBoxSingleton = new wxCheckBox(m_collPane2->GetPane(), wxID_ANY, _("This is a singleton class"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxSingleton->SetValue(false);
    
    fgSizer2->Add(m_checkBoxSingleton, 0, wxALL, 5);
    
    m_checkBoxImplPureVirtual = new wxCheckBox(m_collPane2->GetPane(), wxID_ANY, _("Implement all pure virtual functions"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxImplPureVirtual->SetValue(false);
    
    fgSizer2->Add(m_checkBoxImplPureVirtual, 0, wxALL, 5);
    
    m_checkBoxVirtualDtor = new wxCheckBox(m_collPane2->GetPane(), wxID_ANY, _("Virtual destructor"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxVirtualDtor->SetValue(false);
    
    fgSizer2->Add(m_checkBoxVirtualDtor, 0, wxALL, 5);
    
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer1->Add(buttonSizer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_buttonOK = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonOK->SetDefault();
    
    buttonSizer->Add(m_buttonOK, 0, wxALL, 5);
    
    m_buttonCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    buttonSizer->Add(m_buttonCancel, 0, wxALL, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_textClassName->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(NewClassBaseDlg::OnTextEnter), NULL, this);
    m_buttonBrowseNamespaces->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnBrowseNamespace), NULL, this);
    m_buttonSelectVD->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnBrowseVD), NULL, this);
    m_buttonBrowseFolder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnBrowseFolder), NULL, this);
    m_checkBoxUseUnderscores->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnUseUnderscores), NULL, this);
    m_checkBoxInline->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnCheckInline), NULL, this);
    m_listCtrl1->Connect(wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler(NewClassBaseDlg::OnListItemActivated), NULL, this);
    m_listCtrl1->Connect(wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler(NewClassBaseDlg::OnListItemDeSelected), NULL, this);
    m_listCtrl1->Connect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(NewClassBaseDlg::OnListItemSelected), NULL, this);
    m_buttonAddInheritance->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnButtonAdd), NULL, this);
    m_buttonDelInheritance->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnButtonDelete), NULL, this);
    m_buttonDelInheritance->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewClassBaseDlg::OnButtonDeleteUI), NULL, this);
    m_checkBoxImplVirtual->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnCheckImpleAllVirtualFunctions), NULL, this);
    m_buttonOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnButtonOK), NULL, this);
    m_buttonOK->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewClassBaseDlg::OnOkUpdateUI), NULL, this);
    
}

NewClassBaseDlg::~NewClassBaseDlg()
{
    m_textClassName->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(NewClassBaseDlg::OnTextEnter), NULL, this);
    m_buttonBrowseNamespaces->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnBrowseNamespace), NULL, this);
    m_buttonSelectVD->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnBrowseVD), NULL, this);
    m_buttonBrowseFolder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnBrowseFolder), NULL, this);
    m_checkBoxUseUnderscores->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnUseUnderscores), NULL, this);
    m_checkBoxInline->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnCheckInline), NULL, this);
    m_listCtrl1->Disconnect(wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler(NewClassBaseDlg::OnListItemActivated), NULL, this);
    m_listCtrl1->Disconnect(wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler(NewClassBaseDlg::OnListItemDeSelected), NULL, this);
    m_listCtrl1->Disconnect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(NewClassBaseDlg::OnListItemSelected), NULL, this);
    m_buttonAddInheritance->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnButtonAdd), NULL, this);
    m_buttonDelInheritance->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnButtonDelete), NULL, this);
    m_buttonDelInheritance->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewClassBaseDlg::OnButtonDeleteUI), NULL, this);
    m_checkBoxImplVirtual->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnCheckImpleAllVirtualFunctions), NULL, this);
    m_buttonOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewClassBaseDlg::OnButtonOK), NULL, this);
    m_buttonOK->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewClassBaseDlg::OnOkUpdateUI), NULL, this);
    
}
