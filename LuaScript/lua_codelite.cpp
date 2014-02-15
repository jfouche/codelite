#include "lua_utils.hpp"
#include "imanager.h"
#include "cl_command_event.h"
#include "plugin.h"
#include "event_notifier.h"
#include "lua_event_handler.h"

static int Trace(lua_State* L)
{
	const char* message = lua_tostring(L, 1);
	wxLogMessage(message);
	return 0;
}

static const luaL_Reg METHODS[] = {
	{"Trace", Trace},
	{NULL, NULL}
};

void lua_open_Codelite(lua_State* L, IManager* manager, const char* name)
{
	lua_createtable(L, 0, 0);
	luaL_setfuncs(L, METHODS, 0);

	// add the 'manager' field
	lua_pushstring(L, "manager");
	lua::push(L, manager, "IManager");
	lua_settable(L, -3);

	lua_setglobal(L, name);
}
