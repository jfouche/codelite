#include "lua_workspace.h"
#include "lua_project.h"

static int GetActiveProjectName(lua_State* L)
{
	Workspace* workspace = LuaWorkspace::check(L, 1);
	wxString name = workspace->GetActiveProjectName();
	lua_pushstring(L, name.c_str());
	return 1;
}

static int FindProjectByName(lua_State* L)
{
	Workspace* workspace = LuaWorkspace::check(L, 1);

	printf(lua_stack_dump(L).c_str());

	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* name = lua_tostring(L, 2);
	
	wxString err;
	ProjectPtr project = workspace->FindProjectByName(name, err);
	if (project)
	{
		LuaProject::push(L, project.Get());
	}
	else
	{
		lua_pushnil(L);
	}
	return 1;
}

static int GetProjectList(lua_State* L)
{
	Workspace* workspace = LuaWorkspace::check(L, 1);
	
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

LUA_BINDER_IMPL(Workspace, METHODS);
