#ifndef LUA_RUNNER_H_INCLUDED
#define LUA_RUNNER_H_INCLUDED

#include <imanager.h>
#include "lua_utils.hpp"
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
	template<typename T>
	void RunFunctions(int id, T* event)
	{
		PushOnEventFunctionAndSelf();
		lua_pushnumber(m_lua, id);
		lua::push(m_lua, event);
		lua_call(m_lua, 3, 0);
	}

	void PushOnEventFunctionAndSelf();
};

#endif // LUA_RUNNER_H_INCLUDED
