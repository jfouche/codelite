#ifndef CL_LUA_SCRIPT_MANAGER_H_INCLUDED
#define CL_LUA_SCRIPT_MANAGER_H_INCLUDED

#include <imanager.h>
#include "smart_ptr.h"
#include "lua_runner.h"

#define wxEVT_SCRIPT_ADDED    8001
#define wxEVT_SCRIPT_REMOVED  8002
#define wxEVT_HOOK_ADDED      8003
#define wxEVT_HOOK_REMOVED    8004

class ScriptManager : public wxEvtHandler
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
	
	void Process(int eventId, const wxString& name);
};

typedef SmartPtr<ScriptManager> ScriptMgrPtr;

#endif // CL_LUA_SCRIPT_MANAGER_H_INCLUDED
