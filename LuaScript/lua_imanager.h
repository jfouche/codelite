#ifndef LUA_IMANAGER_H_INCLUDED
#define LUA_IMANAGER_H_INCLUDED

#include "lua_utils.hpp"
#include <imanager.h>

struct IManagerLuaInfos
{
	typedef IManager value_type;
	
	static const char* className;
	static const luaL_Reg metamethods[];
	static const luaL_Reg methods[];
	static const size_t nMethods;
};

typedef LuaBinder<IManagerLuaInfos> LuaIManager;


#endif // LUA_IMANAGER_H_INCLUDED