#include "lua_runner.h"
#include "lua_imanager.h"
#include "lua_ieditor.h"
#include "lua_workspace.h"
#include "lua_project.h"


LuaRunner::LuaRunner(IManager* manager)
: m_manager(manager)
{
	m_lua = luaL_newstate();
	Init();
}

LuaRunner::~LuaRunner()
{
	lua_close(m_lua);
}

void LuaRunner::Init()
{
	luaL_openlibs(m_lua);

	LuaIManager::registerClass(m_lua);
	LuaIEditor::registerClass(m_lua);
	LuaWorkspace::registerClass(m_lua);
	LuaProject::registerClass(m_lua);

	LuaIManager::push(m_lua, m_manager);
	lua_setglobal(m_lua, "cl_manager");
}

void LuaRunner::Run(const wxString& script)
{
	wxLogMessage("[LUA] running %s", script.c_str());
	int status = luaL_loadfile(m_lua, script.c_str());
	if (status != LUA_OK)
	{
		wxLogError("[LUA] can't run %s", script.c_str());
		::wxMessageBox("Can't run script", "Lua plugin error", wxOK|wxICON_ERROR);
		return;
	}
	
	int result = lua_pcall(m_lua, 0, LUA_MULTRET, 0);
	if (result != LUA_OK)
	{
		const char* err = lua_tostring(m_lua, -1);
		wxString msg = wxString::Format("Error %d : %s", result, err);
		wxLogError("[LUA] : %s", msg.c_str());
		::wxMessageBox(msg, "Lua plugin error", wxOK|wxICON_ERROR);
		return;
	}
	wxLogMessage("[LUA] finished");
}

