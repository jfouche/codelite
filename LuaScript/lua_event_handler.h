#ifndef CL_LUA_EVENT_HANDLER_H_INCLUDED
#define CL_LUA_EVENT_HANDLER_H_INCLUDED

#include "script_manager.h"
#include "cl_command_event.h"

class LuaEventHandler : public wxEvtHandler
{
	static LuaEventHandler* INSTANCE;
	
	ScriptMgrPtr m_scriptMgr;
	
private:
	LuaEventHandler(ScriptMgrPtr scriptMgr);
	~LuaEventHandler();

public:
	static void Create(ScriptMgrPtr scriptMgr);
	
	static LuaEventHandler* Get();
	
	void ConnectCmdEvent(int id);
	
protected:
	void OnCmdEvent(wxCommandEvent& event);

	void OnClEvent(clCommandEvent& event);
};

#endif // CL_LUA_EVENT_HANDLER_H_INCLUDED
