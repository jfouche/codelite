#ifndef CL_LUA_EVENT_HANDLER_H_INCLUDED
#define CL_LUA_EVENT_HANDLER_H_INCLUDED

#include "lua_runner.h"
#include <wx/event.h>
#include "cl_command_event.h"

class LuaEventHandler : public wxEvtHandler
{
	static LuaEventHandler* INSTANCE;
	
	LuaRunner& m_runner;
	
private:
	LuaEventHandler(LuaRunner& runner);
	~LuaEventHandler();

public:
	static void Init(LuaRunner& runner);
	
	static LuaEventHandler* Get();

	void onCmdEvent(wxCommandEvent& event);

	void onClEvent(clCommandEvent& event);
};

#endif // CL_LUA_EVENT_HANDLER_H_INCLUDED
