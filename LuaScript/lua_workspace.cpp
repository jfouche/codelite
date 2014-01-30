#include "lua_workspace.h"
#include "lua_project.h"

static int lua_Workspace_GetEditorText(lua_State* L)
{
	Workspace* workspace = LuaWorkspace::check(L, 1);
	return 1;
}

static int lua_Workspace_GetActiveProjectName(lua_State* L)
{
	Workspace* workspace = LuaWorkspace::check(L, 1);
	wxString name = workspace->GetActiveProjectName();
	lua_pushstring(L, name.c_str());
	return 1;
}

static int lua_Workspace_GetProjectList(lua_State* L)
{
	Workspace* workspace = LuaWorkspace::get(L, 1);
	
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
	{"GetActiveProjectName", lua_Workspace_GetActiveProjectName},
	{"GetProjectList", lua_Workspace_GetProjectList},
	{NULL, NULL}
};

LUA_BINDER_IMPL(Workspace, METHODS);
