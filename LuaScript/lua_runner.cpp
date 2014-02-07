#include "lua_runner.h"
#include "lua_utils.hpp"

extern void lua_open_IEditor(lua_State* L);
extern void lua_open_IManager(lua_State* L);
extern void lua_open_Workspace(lua_State* L);
extern void lua_open_Project(lua_State* L);

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

	lua_open_IManager(m_lua);
	lua_open_IEditor(m_lua);
	lua_open_Workspace(m_lua);
	lua_open_Project(m_lua);

	lua::push(m_lua, m_manager, "IManager");
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

