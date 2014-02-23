#include "lua_bindings.h"
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

#define SET_GLOBAL_EVENT(L, e) lua_pushnumber(L, e); lua_setglobal(L, #e)

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

void lua_open_Events(lua_State* L)
{
	lua::createClass(L, WX_EVT_CLASSNAME, WX_METHODS);
	lua_pop(L, 1);

	lua::createClass(L, CL_EVT_CLASSNAME, WX_METHODS);
	luaL_setfuncs(L, CL_METHODS, 0);
	lua_pop(L, 1);

	SET_GLOBAL_EVENT(L, wxEVT_FILE_SAVED);
}
