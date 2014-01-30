#include "lua_project.h"
#include "lua_utils.hpp"

static int lua_Project_GetName(lua_State* L)
{
	Project* project = LuaProject::check(L, 1);
	lua_pushstring(L, project->GetName().c_str());
	return 1;
}

const char* ProjectLuaInfos::className = "luaL_Project";

const luaL_Reg ProjectLuaInfos::methods[] = {
	{"GetName", lua_Project_GetName},
	{NULL, NULL}
};

const luaL_Reg ProjectLuaInfos::metamethods[] = {
	{NULL, NULL}
};

LUA_IMPL_N_METHODS(ProjectLuaInfos);
