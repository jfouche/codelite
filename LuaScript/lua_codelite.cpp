#include "lua_utils.hpp"
#include "lua_event_handler.h"
#include "imanager.h"
#include "cl_command_event.h"
#include "plugin.h"
#include "event_notifier.h"

static const char* MANAGER_FIELD = "manager";
static const char* BINDINGS_FIELD = "bindings";

static int Trace(lua_State* L)
{
	const char* message = lua::check_string(L, 1);
	wxLogMessage(message);
	return 0;
}

static int Bind(lua_State* L)
{
	lua::check_table(L, 1);                   // codelite
	int event_id = lua::check_integer(L, 2);  // event_id
	lua::check_function(L, 3);                // function

	// bindings = codelite.bindings
	lua_getfield(L, 1, BINDINGS_FIELD);

	// functions = bindings[event_id]
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);

	// if functions is nil
	if (lua_isnil(L, -1))
	{
		// Create the initial function table for this event_id
		lua_remove(L, -1);
		
		// functions = {}
		lua_createtable(L, 0, 0);
		
		// bindings[event_id] = functions
		lua_pushvalue(L, 2);
		lua_pushvalue(L, -2);
		lua_settable(L, -4);

		// Bind event on Codelite
		LuaEventHandler::Get()->ConnectCmdEvent(event_id);
	}

	// insert the function at the end of the list
	int i = luaL_len(L, -1) + 1;
	lua_pushinteger(L, i);
	lua_pushvalue(L, 3);
	lua_settable(L, -3);

	// clear stack
	lua_settop(L, 0);

	return 0;
}

static int OnEvent(lua_State* L)
{
	lua::check_table(L, 1);            // codelite
	lua::check_integer(L, 2);          // event_id
	lua::check<wxCommandEvent>(L, 3);  // event

	// bindings = codelite.bindings
	lua_getfield(L, 1, BINDINGS_FIELD);

	// functions = bindings[event_id]
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	
	if (lua_istable(L, -1))
	{
		// for each functions
		lua_pushnil(L); // first index
		while (lua_next(L, -2))
		{
			lua_pushvalue(L, 3); // push the event
			lua_call(L, 1, 0);   // call the function
		}
	}
	
	// clear stack
	lua_settop(L, 0);
	
	return 0;
}

static const luaL_Reg METHODS[] = {
	{"Trace", Trace},
	{"Bind", Bind},
	{"OnEvent", OnEvent},
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
