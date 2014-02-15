#ifndef LUA_RUNNER_H_INCLUDED
#define LUA_RUNNER_H_INCLUDED

#include <imanager.h>
#include "lua.hpp"
#include "cl_command_event.h"

class LuaRunner
{
protected:
	IManager* m_manager;
	lua_State* m_lua;
	
public:
	LuaRunner(IManager* manager);
	virtual ~LuaRunner();

	void Run(const wxString& script);
	
private:
	void Init();
};

class HookRunner : public LuaRunner
{
public:
	HookRunner(IManager* manager);
	
	void onCmdEvent(wxCommandEvent& event);
	void onClEvent(clCommandEvent& event);
	
private:
	void RunFunctions(int id);
};

#endif // LUA_RUNNER_H_INCLUDED
