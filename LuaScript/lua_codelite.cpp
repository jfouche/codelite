#include "lua_utils.hpp"
#include "imanager.h"
#include "cl_command_event.h"
#include "plugin.h"
#include "event_notifier.h"
#include "lua_event_handler.h"

class LuaFunctionEvtHandler : public wxEvtHandler
{
	lua_State* m_lua;
	lua_CFunction m_function;
	
public:
	LuaFunctionEvtHandler(lua_State* L, lua_CFunction fct)
	: m_lua(L)
	, m_function(fct)
	{
	}
	
	void onEvent(wxCommandEvent& event)
	{
		event.Skip(true);
		
		wxLogError("[LUA] LuaFunctionEvtHandler::OnEvent");
		lua_pushcfunction(m_lua, m_function);
		lua::print_stack(m_lua);
		lua_call(m_lua, 0, 0);
		
		printf("EVENT FINISHED"); fflush(stdout);
	}
};

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
