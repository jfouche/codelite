#include "lua_runner.h"
#include "lua_imanager.h"
#include "lua_ieditor.h"


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
	
	LuaIManager::instanciate(m_lua, m_manager);
	lua_setglobal(m_lua, "cl_manager");
}

void LuaRunner::Run(const wxString& script)
{
	wxLogMessage("[LUA] running %s", script.c_str());
	int status = luaL_loadfile(m_lua, script.c_str());
	if (status != LUA_OK)
	{
		wxLogError("[LUA] can't run %s", script.c_str());
		return;
	}
	
	int result = lua_pcall(m_lua, 0, LUA_MULTRET, 0);
	if (result != LUA_OK)
	{
		wxLogError("[LUA] Error %d in %s", result, script.c_str());
		const char* err = lua_tostring(m_lua, -1);
		wxLogError("[LUA] => %s", err);
		return;
	}
	wxLogMessage("[LUA] finished");
}

