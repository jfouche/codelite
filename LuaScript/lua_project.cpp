#include "lua_project.h"

static int GetName(lua_State* L)
{
	Project* project = LuaProject::check(L, 1);
	lua_pushstring(L, project->GetName().c_str());
	return 1;
}

static int GetFiles(lua_State* L)
{
	Project* project = LuaProject::check(L, 1);
	
	wxStringSet_t files;
	project->GetFiles(files);
	
	lua_newtable(L);
	wxStringSet_t::const_iterator itFile = files.begin();
	for (int i = 1; itFile != files.end(); ++itFile, ++i)
	{
		lua_pushstring(L, itFile->c_str());
		lua_rawseti(L, -2, i);
	}
	return 1;
}

static const luaL_Reg METHODS[] = {
	{"GetName", GetName},
	{"GetFiles", GetFiles},
	{NULL, NULL}
};

LUA_BINDER_IMPL(Project, METHODS);
