#include "lua_utils.hpp"
#include "project.h"

static const char* CLASSNAME = "Project";

static int GetName(lua_State* L)
{
	Project* project = lua::check<Project>(L, 1, CLASSNAME);
	lua_pushstring(L, project->GetName().c_str());
	return 1;
}

static int GetFiles(lua_State* L)
{
	Project* project = lua::check<Project>(L, 1, CLASSNAME);
	
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

void lua_open_Project(lua_State* L)
{
	luaL_newmetatable(L, CLASSNAME);
	lua_createtable(L, 0, 0);
	luaL_setfuncs(L, METHODS, 0);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}

