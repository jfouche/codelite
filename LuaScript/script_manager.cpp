#include "script_manager.h"
#include "script_event_handler.h"
#include "lua_runner.h"
#include "cl_standard_paths.h"
#include <wx/filefn.h>
#include <wx/dir.h>

class ScriptTraverser : public wxDirTraverser
{
public:
	ScriptTraverser(wxArrayString& files) : m_files(files) { }

	virtual wxDirTraverseResult OnFile(const wxString& filename)
	{
		wxFileName fn(filename);
		m_files.Add(fn.GetFullName());
		return wxDIR_CONTINUE;
	}
	
	virtual wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname))
	{
		return wxDIR_IGNORE;
	}
	
private:
	wxArrayString& m_files;
};

// =============================================================================

ScriptManager::ScriptManager(IManager* manager)
	: m_manager(manager)
	, m_hookRunner(0)
{
	ScriptEventHandler::Create(this);
	InitHooks();
}

ScriptManager::~ScriptManager()
{
	wxDELETE(m_hookRunner);
}

IManager* ScriptManager::GetManager()
{
	return m_manager;
}

void ScriptManager::InitHooks()
{
	wxDELETE(m_hookRunner);
	m_hookRunner = new HookRunner(m_manager);
	
	wxArrayString hooks;
	GetHooks(hooks);
	
	for (size_t i = 0; i < hooks.size(); ++i)
	{
		wxString hook = GetHookPath(hooks[i]);
		m_hookRunner->Run(hook);
	}
}

void ScriptManager::ScriptManager::Process(int eventId, const wxString& name)
{
	wxCommandEvent event(eventId);
	event.SetString(name);
	ProcessEvent(event);
}

bool ScriptManager::AddScript(const wxString& path)
{
	wxString name = wxFileName(path).GetFullName();
	wxFileName newFile(GetScriptDir(), name);
	if (::wxCopyFile(path, newFile.GetFullPath()) == false)
	{
		return false;
	}
	Process(wxEVT_SCRIPT_ADDED, name);
	return true;
}

bool ScriptManager::AddHook(const wxString& path)
{
	wxString name = wxFileName(path).GetFullName();
	wxFileName newFile(GetHookDir(), name);
	if (::wxCopyFile(path, newFile.GetFullPath()) == false)
	{
		return false;
	}
	Process(wxEVT_HOOK_ADDED, name);
	return true;
}

wxString ScriptManager::GetScriptDir() const
{
	wxString userDir = clStandardPaths::Get().GetUserDataDir();
	wxFileName dir(userDir, "scripts");
	if (dir.Exists(wxFILE_EXISTS_DIR) == false)
	{
		::wxMkDir(dir.GetFullPath(), wxS_DIR_DEFAULT);
	}
	return dir.GetFullPath();
}

void ScriptManager::GetScripts(wxArrayString& scripts) const
{
	ScriptTraverser traverser(scripts);
	wxDir dir(GetScriptDir());
	dir.Traverse(traverser, "*.lua");
}

void ScriptManager::RunScript(const wxString& script)
{
	wxString scriptFile = GetScriptPath(script);
	LuaRunner runner(m_manager);
	runner.Run(scriptFile);
}

bool ScriptManager::DeleteScript(const wxString& script)
{
	wxString scriptFile = GetScriptPath(script);
	if (wxRemoveFile(scriptFile) == false)
	{
		return false;
	}
	Process(wxEVT_SCRIPT_REMOVED, script);
	return true;
}

bool ScriptManager::DeleteHook(const wxString& hook)
{
	wxString hookFile = GetHookPath(hook);
	if (wxRemoveFile(hookFile) == false)
	{
		return false;
	}
	Process(wxEVT_HOOK_REMOVED, hook);
	return true;
}

wxString ScriptManager::GetScriptPath(const wxString& script) const
{
	return wxFileName(GetScriptDir(), script).GetFullPath();
}

wxString ScriptManager::GetHookDir() const
{
	wxString userDir = clStandardPaths::Get().GetUserDataDir();
	wxFileName dir(userDir, "hooks");
	if (dir.Exists(wxFILE_EXISTS_DIR) == false)
	{
		::wxMkDir(dir.GetFullPath(), wxS_DIR_DEFAULT);
	}
	return dir.GetFullPath();
}

void ScriptManager::GetHooks(wxArrayString& hooks) const
{
	ScriptTraverser traverser(hooks);
	wxDir dir(GetHookDir());
	dir.Traverse(traverser, "*.lua");
}

wxString ScriptManager::GetHookPath(const wxString& hook) const
{
	return wxFileName(GetHookDir(), hook).GetFullPath();
}

void ScriptManager::OnCmdEvent(wxCommandEvent& event)
{
	m_hookRunner->OnCmdEvent(event);
}

void ScriptManager::ReloadHooks()
{
	InitHooks();
}
