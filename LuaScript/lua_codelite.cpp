#include "lua_utils.hpp"
#include "imanager.h"

static const char* CLASSNAME = "Codelite";

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
	luaL_newmetatable(L, CLASSNAME);
	lua_createtable(L, 0, 0);
	lua_pushvalue(L, 1); // keep a copy of table, to set it global
	luaL_setfuncs(L, METHODS, 0);
	lua_setfield(L, -3, "__index");
	lua_pop(L, 1);

	// add the 'manager' field
	lua_pushstring(L, "manager");
	lua::push(L, manager, "IManager");
	lua_settable(L, -3);

	lua_setglobal(L, name);
}
