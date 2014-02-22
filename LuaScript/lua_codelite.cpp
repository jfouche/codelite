#include "lua_utils.hpp"
#include "imanager.h"
#include "cl_command_event.h"
#include "plugin.h"

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
	lua::createClass(L, "CODELITE", METHODS);

	// add the 'manager' field
	lua_pushstring(L, "manager");
	lua::push(L, manager);
	lua_settable(L, -3);

	lua_setglobal(L, name);
}
