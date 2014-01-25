#ifndef LUA_RUNNER_H_INCLUDED
#define LUA_RUNNER_H_INCLUDED

#include <imanager.h>
#include "lua.hpp"

class LuaRunner
{
	IManager* m_manager;
	lua_State* m_lua;
	
public:
	LuaRunner(IManager* manager);
	~LuaRunner();

	void Run(const wxString& script);
	
private:
	void Init();
};

#endif // LUA_RUNNER_H_INCLUDED
