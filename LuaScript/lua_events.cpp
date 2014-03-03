#include "lua_cl_bindings.h"
#include "plugin.h"
#include "cl_command_event.h"

namespace lua
{
	template <>
	void push(lua_State* L, wxCommandEvent* instance)
	{
		push(L, instance, WX_EVT_CLASSNAME);
	}

	template <>
	wxCommandEvent* check(lua_State* L, int n)
	{
		return check<wxCommandEvent>(L, n, WX_EVT_CLASSNAME);
	}

	template <>
	void push(lua_State* L, clCommandEvent* instance)
	{
		push(L, instance, CL_EVT_CLASSNAME);
	}

	template <>
	clCommandEvent* check(lua_State* L, int n)
	{
		return check<clCommandEvent>(L, n, CL_EVT_CLASSNAME);
	}
}

static int GetString(lua_State* L)
{
	wxCommandEvent* event = lua::check<wxCommandEvent>(L, 1);
	lua_pushstring(L, event->GetString().c_str());
	return 1;
}

static int GetFileName(lua_State* L)
{
	clCommandEvent* event = lua::check<clCommandEvent>(L, 1);
	lua_pushstring(L, event->GetFileName().c_str());
	return 1;
}

static const luaL_Reg WX_METHODS[] = {
	{"GetString", GetString},
	{NULL, NULL}
};

static const luaL_Reg CL_METHODS[] = {
	{"GetFileName", GetFileName},
	{NULL, NULL}
};

#define SET_GLOBAL_EVENT(L, e) lua_pushnumber(L, e); lua_setglobal(L, #e)

void lua_open_Events(lua_State* L)
{
	lua::createClass(L, WX_EVT_CLASSNAME, WX_METHODS);
	lua_pop(L, 1);

	lua::createClass(L, CL_EVT_CLASSNAME, WX_METHODS);
	luaL_setfuncs(L, CL_METHODS, 0);
	lua_pop(L, 1);

	SET_GLOBAL_EVENT(L, wxEVT_INIT_DONE);
	SET_GLOBAL_EVENT(L, wxEVT_EDITOR_CONFIG_CHANGED);
	SET_GLOBAL_EVENT(L, wxEVT_WORKSPACE_CONFIG_CHANGED);
	SET_GLOBAL_EVENT(L, wxEVT_WORKSPACE_CLOSED);
	SET_GLOBAL_EVENT(L, wxEVT_FILE_VIEW_INIT_DONE);
	SET_GLOBAL_EVENT(L, wxEVT_TREE_ITEM_FILE_ACTIVATED);
	SET_GLOBAL_EVENT(L, wxEVT_PROJ_FILE_ADDED);
	SET_GLOBAL_EVENT(L, wxEVT_PROJ_FILE_REMOVED);
	SET_GLOBAL_EVENT(L, wxEVT_PROJ_REMOVED);
	SET_GLOBAL_EVENT(L, wxEVT_PROJ_ADDED);
	SET_GLOBAL_EVENT(L, wxEVT_FILE_SAVE_BY_BUILD_END);
	SET_GLOBAL_EVENT(L, wxEVT_FILE_SAVE_BY_BUILD_START);
	SET_GLOBAL_EVENT(L, wxEVT_FILE_SAVED);
	SET_GLOBAL_EVENT(L, wxEVT_FILE_RETAGGED);
	SET_GLOBAL_EVENT(L, wxEVT_FILE_RENAMED);
	SET_GLOBAL_EVENT(L, wxEVT_ACTIVE_EDITOR_CHANGED);
	SET_GLOBAL_EVENT(L, wxEVT_EDITOR_CLOSING);
	SET_GLOBAL_EVENT(L, wxEVT_ALL_EDITORS_CLOSING);
	SET_GLOBAL_EVENT(L, wxEVT_ALL_EDITORS_CLOSED);
	SET_GLOBAL_EVENT(L, wxEVT_EDITOR_CLICKED);
	SET_GLOBAL_EVENT(L, wxEVT_EDITOR_SETTINGS_CHANGED);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_PROJ_SETTINGS_SAVED);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_EXECUTE_ACTIVE_PROJECT);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_CREATE_NEW_WORKSPACE);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_CREATE_NEW_PROJECT);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_OPEN_WORKSPACE);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_CLOSE_WORKSPACE);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_EDITOR_TIP_DWELL_END);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_RETAG_COMPLETED);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_PAGE_CHANGED);
	SET_GLOBAL_EVENT(L, wxEVT_ACTIVE_PROJECT_CHANGED);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_BUILD_PROJECT_ONLY);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_CLEAN_PROJECT_ONLY);
	SET_GLOBAL_EVENT(L, wxEVT_CMD_OPEN_PROJ_SETTINGS);
}
