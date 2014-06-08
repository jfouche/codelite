#include "script_frame.h"
#include <wx/listbox.h>
#include <wx/log.h>

ScriptFrame::ScriptFrame(wxWindow* parent, ScriptMgrPtr scriptMgr)
: wxMiniFrame(parent, wxID_ANY, _("Scripts"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxRESIZE_BORDER|wxSTAY_ON_TOP)
, m_scriptMgr(scriptMgr)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);

	m_scripts = new wxListBox(this, wxID_ANY);
	sizer->Add(m_scripts, 1, wxALL|wxEXPAND, 0);

	SetSizeHints(200,300);
	sizer->Fit(this);

	SetTransparent(210);

    m_scripts->Connect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(ScriptFrame::OnRunScript), NULL, this);
	UpdateScripts();

	m_scriptMgr->Connect(wxEVT_SCRIPT_ADDED,   wxCommandEventHandler(ScriptFrame::OnScriptsChanged), NULL, this);
	m_scriptMgr->Connect(wxEVT_SCRIPT_REMOVED, wxCommandEventHandler(ScriptFrame::OnScriptsChanged), NULL, this);

	Show(false);
}

void ScriptFrame::UpdateScripts()
{
	wxArrayString scripts;
	m_scriptMgr->GetScripts(scripts);
	m_scripts->Set(scripts);
}

void ScriptFrame::OnRunScript(wxCommandEvent& event)
{
	wxString script = m_scripts->GetStringSelection();
	if (script.IsEmpty() == false)
	{
		m_scriptMgr->RunScript(script);
	}
}

void ScriptFrame::OnScriptsChanged(wxCommandEvent& event)
{
	UpdateScripts();
}
