#ifndef CL_LUA_PROJECT_H_INCLUDED
#define CL_LUA_PROJECT_H_INCLUDED

#include "lua_utils.hpp"
#include "project.h"

struct ProjectLuaInfos
{
	typedef Project value_type;
	
	static const char* className;
	static const luaL_Reg metamethods[];
	static const luaL_Reg methods[];
	static const size_t nMethods;
};

typedef LuaBinder<ProjectLuaInfos> LuaProject;

#endif // CL_LUA_PROJECT_H_INCLUDED
