#ifndef CL_LUA_SCRIPT_MANAGER_H_INCLUDED
#define CL_LUA_SCRIPT_MANAGER_H_INCLUDED

#include <imanager.h>
#include "smart_ptr.h"
#include "lua_runner.h"

class ScriptManager
{
	IManager* m_manager;
	HookRunner* m_hookRunner;

public:
	ScriptManager(IManager* manager);
	~ScriptManager();

	IManager* GetManager();

	bool AddScript(const wxString& path);
	
	void GetScripts(wxArrayString& scripts) const;
	
	void RunScript(const wxString& script);
	
	bool DeleteScript(const wxString& script);
	
	wxString GetScriptPath(const wxString& script) const;

	bool AddHook(const wxString& path);

	bool DeleteHook(const wxString& script);
	
	void GetHooks(wxArrayString& hooks) const;

	wxString GetHookPath(const wxString& hook) const;
	
	void ReloadHooks();

	void OnCmdEvent(wxCommandEvent& event);
	void OnClEvent(clCommandEvent& event);

private:
	wxString GetScriptDir() const;
	wxString GetHookDir() const;
	
	void InitHooks();
};

typedef SmartPtr<ScriptManager> ScriptMgrPtr;

#endif // CL_LUA_SCRIPT_MANAGER_H_INCLUDED
