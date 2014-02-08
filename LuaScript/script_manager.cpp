#include "script_manager.h"
#include "lua_runner.h"
#include "cl_standard_paths.h"
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
{
}

ScriptManager::~ScriptManager()
{
}

IManager* ScriptManager::GetManager()
{
	return m_manager;
}

bool ScriptManager::AddScript(const wxString& path)
{
	wxFileName file(path);
	wxFileName newFile(GetScriptDir(), file.GetFullName());
	return ::wxCopyFile(path, newFile.GetFullPath());
}

wxString ScriptManager::GetScriptDir() const
{
	wxString userDir = clStandardPaths::Get().GetUserDataDir();
	wxFileName dir(userDir, "scripts");
	if (dir.Exists(wxFILE_EXISTS_DIR) == false)
	{
		::wxMkDir(dir.GetFullPath());
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
	return wxRemoveFile(scriptFile);
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
		::wxMkDir(dir.GetFullPath());
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
