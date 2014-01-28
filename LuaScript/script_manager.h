#ifndef CL_LUA_SCRIPT_MANAGER_H_INCLUDED
#define CL_LUA_SCRIPT_MANAGER_H_INCLUDED

#include <imanager.h>

class ScriptManager
{
	IManager* m_manager;
	
public:
	ScriptManager(IManager* manager);
	~ScriptManager();

	IManager* GetManager();

	bool AddScript(const wxString& path);
	
	void GetScripts(wxArrayString& scripts) const;
	
	void RunScript(const wxString& script);
	
	bool DeleteScript(const wxString& script);
	
	wxString GetScriptPath(const wxString& script) const;
	
private:
	wxString GetScriptDir() const;
};

#endif // CL_LUA_SCRIPT_MANAGER_H_INCLUDED
