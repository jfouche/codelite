//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef WXCRAFTER_BASE_CLASSES_H
#define WXCRAFTER_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/listbook.h>
#include <wx/panel.h>
#include <wx/imaglist.h>
#include <wx/listbox.h>
#include <wx/button.h>

class ScriptSettingsDialogBase : public wxDialog
{
protected:
    wxListbook* m_listbook292;
    wxPanel* m_panel313;
    wxListBox* m_listScripts;
    wxButton* m_btnAddScript;
    wxButton* m_btnDeleteScript;
    wxButton* m_btnEditScript;
    wxPanel* m_panel3310;
    wxListBox* m_listHooks;
    wxButton* m_btnAddHook;
    wxButton* m_btnDeleteHook;
    wxButton* m_btnEditHook;
    wxButton* m_btnReloadHooks;

protected:
    virtual void OnAddScripts(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteScript(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUpdateUi(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnEditScript(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAddHook(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteHook(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEditHook(wxCommandEvent& event) { event.Skip(); }
    virtual void OnReloadHooks(wxCommandEvent& event) { event.Skip(); }

public:
    ScriptSettingsDialogBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Script plugin settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~ScriptSettingsDialogBase();
};

#endif