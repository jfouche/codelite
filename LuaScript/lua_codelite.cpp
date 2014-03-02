#include "lua_utils.hpp"
#include "imanager.h"
#include "cl_command_event.h"
#include "plugin.h"

static const char* MANAGER_FIELD = "manager";
static const char* BINDINGS_FIELD = "__bindings";


static int Trace(lua_State* L)
{
	const char* message = lua::check_string(L, 1);
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
	lua::push(L, manager);
	lua_setfield(L, -2, MANAGER_FIELD);
	
	// add the private '__bindings' field
	lua_createtable(L, 0, 0);
	lua_setfield(L, -2, BINDINGS_FIELD);

	lua_setglobal(L, name);
}
