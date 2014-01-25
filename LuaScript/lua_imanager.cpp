#include "lua_imanager.h"
#include "lua_ieditor.h"

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
		LuaIEditor::instanciate(L, editor);
	}
	return 1;
}

const char* IManagerLuaInfos::className = "luaL_IManager";

const luaL_Reg IManagerLuaInfos::methods[] = {
	{"GetActiveEditor", lua_IManager_GetActiveEditor},
	{NULL, NULL}
};

const luaL_Reg IManagerLuaInfos::metamethods[] = {
	{NULL, NULL}
};

const size_t IManagerLuaInfos::nMethods = METHODS_COUNT(IManagerLuaInfos::methods);
