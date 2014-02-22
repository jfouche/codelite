#include "lua_bindings.h"
#include "workspace.h"


namespace lua
{
	template <>
	void push(lua_State* L, Workspace* instance)
	{
		push(L, instance, WORKSPACE_CLASSNAME);
	}

	template <>
	Workspace* check(lua_State* L, int n)
	{
		return check<Workspace>(L, n, WORKSPACE_CLASSNAME);
	}
}

static int GetActiveProjectName(lua_State* L)
{
	Workspace* workspace = lua::check<Workspace>(L, 1);
	wxString name = workspace->GetActiveProjectName();
	lua_pushstring(L, name.c_str());
	return 1;
}

static int FindProjectByName(lua_State* L)
{
	Workspace* workspace = lua::check<Workspace>(L, 1);

	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* name = lua_tostring(L, 2);
	
	wxString err;
	ProjectPtr project = workspace->FindProjectByName(name, err);
	if (project)
	{
		lua::push(L, project.Get());
	}
	else
	{
		lua_pushnil(L);
	}
	return 1;
}

static int GetProjectList(lua_State* L)
{
	Workspace* workspace = lua::check<Workspace>(L, 1);
	
	wxArrayString names;
	workspace->GetProjectList(names);
	
	lua_newtable(L);
	for (size_t i = 0; i < names.size(); ++i)
	{
		wxString name = names[i];
		lua_pushstring(L, names[i].c_str());
		lua_rawseti(L, -2, i+1);
	}
	return 1;
}

static luaL_Reg METHODS[] = {
	{"GetActiveProjectName", GetActiveProjectName},
	{"GetProjectList", GetProjectList},
	{"FindProjectByName", FindProjectByName},
	{NULL, NULL}
};

void lua_open_Workspace(lua_State* L)
{
	lua::createClass(L, WORKSPACE_CLASSNAME, METHODS);
	lua_pop(L, 1);
}
