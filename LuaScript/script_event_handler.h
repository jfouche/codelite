#ifndef CL_LUA_EVENT_HANDLER_H_INCLUDED
#define CL_LUA_EVENT_HANDLER_H_INCLUDED

#include "script_manager.h"
#include "cl_command_event.h"

class ScriptEventHandler : public wxEvtHandler
{
	static ScriptEventHandler* INSTANCE;
	
	ScriptMgrPtr m_scriptMgr;
	
private:
	ScriptEventHandler(ScriptMgrPtr scriptMgr);
	~ScriptEventHandler();

public:
	static void Create(ScriptMgrPtr scriptMgr);
	
	static ScriptEventHandler* Get();
	
	void ConnectCmdEvent(int id);
	
protected:
	void OnCmdEvent(wxCommandEvent& event);
};

#endif // CL_LUA_EVENT_HANDLER_H_INCLUDED
