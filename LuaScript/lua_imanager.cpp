#include "lua_utils.hpp"
#include "imanager.h"
#include "workspace.h"

static const char* CLASSNAME = "IManager";

namespace lua
{
	template <>
	void push(lua_State* L, IManager* instance)
	{
		push(L, instance, CLASSNAME);
	}

	template <>
	IManager* check(lua_State* L, int n)
	{
		return check<IManager>(L, n, CLASSNAME);
	}
}

static int GetActiveEditor(lua_State* L)
{
	IManager* manager = lua::check<IManager>(L, 1);
	IEditor* editor = manager->GetActiveEditor();
	if (editor == NULL)
	{
		lua_pushnil(L);
	}
	else
	{
		lua::push(L, editor);
	}
	return 1;
}

static int NewEditor(lua_State* L)
{
	IManager* manager = lua::check<IManager>(L, 1);
	IEditor* editor = manager->NewEditor();
	lua::push(L, editor);
	return 1;
}

static int GetWorkspace(lua_State* L)
{
	IManager* manager = lua::check<IManager>(L, 1);
	Workspace* workspace = manager->GetWorkspace();
	if (workspace->IsOpen())
	{
		lua::push(L, workspace);
	}
	else
	{
		lua_pushnil(L);
	}
	return 1;
}

const luaL_Reg METHODS[] = {
	{"GetActiveEditor", GetActiveEditor},
	{"NewEditor", NewEditor},
	{"GetWorkspace", GetWorkspace },
	{NULL, NULL}
};

void lua_open_IManager(lua_State* L)
{
	luaL_newmetatable(L, CLASSNAME);
	lua_createtable(L, 0, 0);
	luaL_setfuncs(L, METHODS, 0);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}
