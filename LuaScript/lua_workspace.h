#ifndef CL_LUA_WORKSPACE_H_INCLUDED
#define CL_LUA_WORKSPACE_H_INCLUDED

#include "lua_utils.hpp"
#include "workspace.h"

struct WorkspaceLuaInfos
{
	typedef Workspace value_type;
	
	static const char* className;
	static const luaL_Reg metamethods[];
	static const luaL_Reg methods[];
	static const size_t nMethods;
};

typedef LuaBinder<WorkspaceLuaInfos> LuaWorkspace;

#endif // CL_LUA_WORKSPACE_H_INCLUDED
