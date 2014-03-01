#include "lua_cl_bindings.h"
#include "project.h"


namespace lua
{
	template <>
	void push(lua_State* L, Project* instance)
	{
		push(L, instance, PROJECT_CLASSNAME);
	}

	template <>
	Project* check(lua_State* L, int n)
	{
		return check<Project>(L, n, PROJECT_CLASSNAME);
	}
}

static int GetName(lua_State* L)
{
	Project* project = lua::check<Project>(L, 1);
	lua_pushstring(L, project->GetName().c_str());
	return 1;
}

static int GetFiles(lua_State* L)
{
	Project* project = lua::check<Project>(L, 1);
	
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
	lua::createClass(L, PROJECT_CLASSNAME, METHODS);
	lua_pop(L, 1);
}

