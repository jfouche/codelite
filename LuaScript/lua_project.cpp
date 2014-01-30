#include "lua_project.h"

static int lua_Project_GetName(lua_State* L)
{
	Project* project = LuaProject::check(L, 1);
	lua_pushstring(L, project->GetName().c_str());
	return 1;
}

static const luaL_Reg METHODS[] = {
	{"GetName", lua_Project_GetName},
	{NULL, NULL}
};

LUA_BINDER_IMPL(Project, METHODS);
