#ifndef LUA_RUNNER_H_INCLUDED
#define LUA_RUNNER_H_INCLUDED

#include <imanager.h>
#include <setjmp.h>
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

	static jmp_buf JUMP_BUFFER;

	void Run(const wxString& script);
	
private:
	void Init();
};

class HookRunner : public LuaRunner
{
public:
	HookRunner(IManager* manager);
	
	void OnCmdEvent(wxCommandEvent& event);
	void OnClEvent(clCommandEvent& event);
	
private:
	template<typename T>
	void RunFunctions(int id, T* event)
	{
		PushOnEventFunctionAndSelf();
		lua_pushnumber(m_lua, id);
		lua::push(m_lua, event);

		if (setjmp(JUMP_BUFFER) == 0)
		{
			lua_call(m_lua, 3, 0);
		}
	}

	void PushOnEventFunctionAndSelf();
};

#endif // LUA_RUNNER_H_INCLUDED
