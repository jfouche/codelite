#ifndef SCRIPTSETTINGSDIALOG_H
#define SCRIPTSETTINGSDIALOG_H

#include "wxcrafter_lua_script.h"
#include "script_manager.h"

class ScriptSettingsDialog : public ScriptSettingsDialogBase
{
	ScriptMgrPtr m_scriptMgr;

public:
    ScriptSettingsDialog(wxWindow* parent, ScriptMgrPtr scriptMgr);
    virtual ~ScriptSettingsDialog();

private:
	void RefreshScripts();
	void RefreshHooks();

protected:
    virtual void OnAddScripts(wxCommandEvent& event);
    virtual void OnDeleteScript(wxCommandEvent& event);
    virtual void OnEditScript(wxCommandEvent& event);
};
#endif // SCRIPTSETTINGSDIALOG_H
