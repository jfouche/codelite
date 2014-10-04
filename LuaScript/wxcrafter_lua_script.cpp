//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "wxcrafter_lua_script.h"


// Declare the bitmap loading function
extern void wxC71ADInitBitmapResources();

static bool bBitmapLoaded = false;


ScriptSettingsDialogBase::ScriptSettingsDialogBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC71ADInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer271 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer271);
    
    m_listbook292 = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxLB_DEFAULT|wxBK_DEFAULT);
    
    boxSizer271->Add(m_listbook292, 1, wxALL|wxEXPAND, 5);
    
    m_panel313 = new wxPanel(m_listbook292, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_listbook292->AddPage(m_panel313, _("Scripts"), false);
    
    wxBoxSizer* boxSizer354 = new wxBoxSizer(wxHORIZONTAL);
    m_panel313->SetSizer(boxSizer354);
    
    wxArrayString m_listScriptsArr;
    m_listScripts = new wxListBox(m_panel313, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_listScriptsArr, wxLB_SINGLE);
    
    boxSizer354->Add(m_listScripts, 1, wxEXPAND, 5);
    
    wxBoxSizer* boxSizer396 = new wxBoxSizer(wxVERTICAL);
    
    boxSizer354->Add(boxSizer396, 0, wxALL|wxALIGN_TOP, 5);
    
    m_btnAddScript = new wxButton(m_panel313, wxID_ANY, _("Add..."), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer396->Add(m_btnAddScript, 0, wxALL, 5);
    
    m_btnDeleteScript = new wxButton(m_panel313, wxID_ANY, _("Delete"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer396->Add(m_btnDeleteScript, 0, wxALL, 5);
    
    m_btnEditScript = new wxButton(m_panel313, wxID_ANY, _("Edit"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer396->Add(m_btnEditScript, 0, wxALL, 5);
    
    m_panel3310 = new wxPanel(m_listbook292, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_listbook292->AddPage(m_panel3310, _("Hooks"), false);
    
    wxBoxSizer* boxSizer35711 = new wxBoxSizer(wxHORIZONTAL);
    m_panel3310->SetSizer(boxSizer35711);
    
    wxArrayString m_listHooksArr;
    m_listHooks = new wxListBox(m_panel3310, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_listHooksArr, wxLB_SINGLE);
    
    boxSizer35711->Add(m_listHooks, 1, wxEXPAND, 5);
    
    wxBoxSizer* boxSizer39913 = new wxBoxSizer(wxVERTICAL);
    
    boxSizer35711->Add(boxSizer39913, 0, wxALL|wxALIGN_TOP, 5);
    
    m_btnAddHook = new wxButton(m_panel3310, wxID_ANY, _("Add..."), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer39913->Add(m_btnAddHook, 0, wxALL, 5);
    
    m_btnDeleteHook = new wxButton(m_panel3310, wxID_ANY, _("Delete"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer39913->Add(m_btnDeleteHook, 0, wxALL, 5);
    
    m_btnEditHook = new wxButton(m_panel3310, wxID_ANY, _("Edit"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer39913->Add(m_btnEditHook, 0, wxALL, 5);
    
    m_btnReloadHooks = new wxButton(m_panel3310, wxID_ANY, _("Reload"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_btnReloadHooks->SetToolTip(_("Reload all hook script, to take in account last modifications"));
    
    boxSizer39913->Add(m_btnReloadHooks, 0, wxALL, 5);
    
    SetSizeHints(500,300);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_btnAddScript->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnAddScripts), NULL, this);
    m_btnDeleteScript->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnDeleteScript), NULL, this);
    m_btnDeleteScript->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnEditScript->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnEditScript), NULL, this);
    m_btnEditScript->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnAddHook->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnAddHook), NULL, this);
    m_btnDeleteHook->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnDeleteHook->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnDeleteHook), NULL, this);
    m_btnEditHook->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnEditHook->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnEditHook), NULL, this);
    m_btnReloadHooks->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnReloadHooks), NULL, this);
    
}

ScriptSettingsDialogBase::~ScriptSettingsDialogBase()
{
    m_btnAddScript->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnAddScripts), NULL, this);
    m_btnDeleteScript->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnDeleteScript), NULL, this);
    m_btnDeleteScript->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnEditScript->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnEditScript), NULL, this);
    m_btnEditScript->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnAddHook->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnAddHook), NULL, this);
    m_btnDeleteHook->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnDeleteHook->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnDeleteHook), NULL, this);
    m_btnEditHook->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptSettingsDialogBase::OnUpdateUi), NULL, this);
    m_btnEditHook->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnEditHook), NULL, this);
    m_btnReloadHooks->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScriptSettingsDialogBase::OnReloadHooks), NULL, this);
    
}