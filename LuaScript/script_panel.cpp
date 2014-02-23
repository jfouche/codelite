#include "script_panel.h"

ScriptPanel::ScriptPanel(wxWindow* parent, ScriptMgrPtr scriptMgr)
    : ScriptPanelBase(parent)
	, m_scriptMgr(scriptMgr)
{
	RefreshList();
}

ScriptPanel::~ScriptPanel()
{
}

IManager* ScriptPanel::GetManager()
{
	return m_scriptMgr->GetManager();
}

void ScriptPanel::RefreshList()
{
	wxArrayString scripts;
	m_scriptMgr->GetScripts(scripts);
	m_listScripts->Set(scripts);
}

void ScriptPanel::onAddScript(wxCommandEvent& event)
{
	wxWindow* frame = GetManager()->GetTheApp()->GetTopWindow();
	wxFileDialog dlg(frame, _("Add a script"), "", "", _("lua file|*.lua"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	
	wxString path = dlg.GetPath();
	if (m_scriptMgr->AddScript(path) == false)
	{
		::wxMessageBox(_("Can't add script"), _("Script"));
		return;
	}
	RefreshList();
}

void ScriptPanel::OnRunScript(wxCommandEvent& event)
{
	wxString script = m_listScripts->GetStringSelection();
	if (script.IsEmpty() == false)
	{
		m_scriptMgr->RunScript(script);
	}
}

void ScriptPanel::OnEditScript(wxCommandEvent& event)
{
	wxString script = m_listScripts->GetStringSelection();
	if (script.IsEmpty())
	{
		return;
	}
	wxString scriptPath = m_scriptMgr->GetScriptPath(script);
	if (wxFileExists(scriptPath))
	{
		GetManager()->OpenFile(scriptPath);
	}
}

void ScriptPanel::OnDeleteScript(wxCommandEvent& event)
{
	wxString script = m_listScripts->GetStringSelection();
	if (script.IsEmpty() == false)
	{
		if (m_scriptMgr->DeleteScript(script))
		{
			RefreshList();
		}
	}
}
