#include "lua_imanager.h"
#include "lua_ieditor.h"
#include "lua_workspace.h"

static int lua_IManager_GetActiveEditor(lua_State* L)
{
	IManager* manager = LuaIManager::check(L, 1);
	IEditor* editor = manager->GetActiveEditor();
	if (editor == NULL)
	{
		lua_pushnil(L);
	}
	else
	{
		LuaIEditor::push(L, editor);
	}
	return 1;
}

static int lua_IManager_NewEditor(lua_State* L)
{
	IManager* manager = LuaIManager::check(L, 1);
	IEditor* editor = manager->NewEditor();
	LuaIEditor::push(L, editor);
	return 1;
}

static int lua_IManager_GetWorkspace(lua_State* L)
{
	IManager* manager = LuaIManager::check(L, 1);
	Workspace* workspace = manager->GetWorkspace();
	if (workspace->IsOpen())
	{
		LuaWorkspace::push(L,workspace);
	}
	else
	{
		lua_pushnil(L);
	}
	return 1;
}

const char* IManagerLuaInfos::className = "luaL_IManager";

const luaL_Reg IManagerLuaInfos::methods[] = {
	{"GetActiveEditor", lua_IManager_GetActiveEditor},
	{"NewEditor", lua_IManager_NewEditor},
	{"GetWorkspace", lua_IManager_GetWorkspace },
	{NULL, NULL}
};

const luaL_Reg IManagerLuaInfos::metamethods[] = {
	{NULL, NULL}
};

LUA_IMPL_N_METHODS(IManagerLuaInfos);
