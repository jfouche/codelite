#ifndef CL_LUA_SCRIPT_PANEL_H
#define CL_LUA_SCRIPT_PANEL_H

#include "wxcrafter_lua_script.h"
#include "script_manager.h"

class IManager;

class ScriptPanel : public ScriptPanelBase
{
	ScriptMgrPtr m_scriptMgr;
	
public:
    ScriptPanel(wxWindow* parent, ScriptMgrPtr scriptMgr);
    virtual ~ScriptPanel();

protected:
    virtual void OnEditScript(wxCommandEvent& event);
    virtual void OnDeleteScript(wxCommandEvent& event);
    virtual void OnRunScript(wxCommandEvent& event);
    virtual void onAddScript(wxCommandEvent& event);

private:
	IManager* GetManager();
	void RefreshList();
};

#endif // CL_LUA_SCRIPT_PANEL_H
