#include "lua_utils.hpp"
#include "cl_command_event.h"

static const char* CMD_EVT_CLASSNAME = "CommandEvent";

namespace lua
{
	template <>
	void push(lua_State* L, wxCommandEvent* instance)
	{
		push(L, instance, CMD_EVT_CLASSNAME);
	}

	template <>
	wxCommandEvent* check(lua_State* L, int n)
	{
		return check<wxCommandEvent>(L, n, CMD_EVT_CLASSNAME);
	}
}

static int GetString(lua_State* L)
{
	wxCommandEvent* event = lua::check<wxCommandEvent>(L, 1);
	event->GetString();
	return 1;
}

static const luaL_Reg METHODS[] = {
	{"GetString", GetString},
	{NULL, NULL}
};

void lua_open_Events(lua_State* L)
{
	luaL_newmetatable(L, CMD_EVT_CLASSNAME);
	lua_createtable(L, 0, 0);
	luaL_setfuncs(L, METHODS, 0);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);

}
