#include "script_settings_dlg.h"

ScriptSettingsDialog::ScriptSettingsDialog(wxWindow* parent, ScriptMgrPtr scriptMgr)
    : ScriptSettingsDialogBase(parent)
	, m_scriptMgr(scriptMgr)
{
	RefreshScripts();
	RefreshHooks();
}

ScriptSettingsDialog::~ScriptSettingsDialog()
{
}

void ScriptSettingsDialog::RefreshHooks()
{
	wxArrayString hooks;
	m_scriptMgr->GetHooks(hooks);
	m_listHooks->Set(hooks);
}

void ScriptSettingsDialog::RefreshScripts()
{
	wxArrayString scripts;
	m_scriptMgr->GetScripts(scripts);
	m_listScripts->Set(scripts);
}

void ScriptSettingsDialog::OnAddScripts(wxCommandEvent& event)
{
	wxFileDialog dlg(this, _("Add a script"), "", "", _("lua file|*.lua"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	
	wxString path = dlg.GetPath();
	if (m_scriptMgr->AddScript(path) == false)
	{
		::wxMessageBox(_("Can't add script"), _("Script"));
		return;
	}
	RefreshScripts();
}

void ScriptSettingsDialog::OnDeleteScript(wxCommandEvent& event)
{
	wxString script = m_listScripts->GetStringSelection();
	if (script.IsEmpty() == false)
	{
		if (m_scriptMgr->DeleteScript(script))
		{
			RefreshScripts();
		}
	}
}

void ScriptSettingsDialog::OnEditScript(wxCommandEvent& event)
{
	wxString script = m_listScripts->GetStringSelection();
	if (script.IsEmpty())
	{
		return;
	}
	wxString scriptPath = m_scriptMgr->GetScriptPath(script);
	if (wxFileExists(scriptPath))
	{
		m_scriptMgr->GetManager()->OpenFile(scriptPath);
	}
}
