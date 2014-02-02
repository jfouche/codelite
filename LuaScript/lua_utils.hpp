#ifndef CL_LUA_UTILS_H_INCLUDED
#define CL_LUA_UTILS_H_INCLUDED

#include <lua.hpp>
#include <string>

/**
 *
 */
template <typename T>
struct LuaBinder
{
	typedef typename T::value_type  value_type;
	
	static value_type* check(lua_State* L, int n)
	{
		return *(value_type**)luaL_checkudata(L, n, T::className);
	}

	static void registerClass(lua_State* L)
	{
		luaL_newmetatable(L, T::className);
		if (T::metamethods == NULL)
		{
			static const luaL_Reg NO_METAS[] = {
				{NULL, NULL}
			};
			luaL_setfuncs(L, NO_METAS, 0);
		}
		else
		{
			luaL_setfuncs(L, T::metamethods, 0);
		}
		lua_createtable(L, 0, 0);
		luaL_setfuncs(L, T::methods, 0);
		lua_setfield(L, -2, "__index");
		lua_pop(L, 1);
	}
	
	static void push(lua_State* L, value_type* instance)
	{
		value_type** udata = static_cast<value_type**>(lua_newuserdata(L, sizeof(void*)));
		*udata = instance;
		luaL_getmetatable(L, T::className);
		lua_setmetatable(L, -2);
	}
};

std::string lua_stack_dump(lua_State *L);

#define LUA_BINDER_DEFINE(CLASS, BINDER) \
	struct CLASS##LuaInfos \
	{ \
		typedef CLASS value_type; \
		static const char* className; \
		static const luaL_Reg* methods; \
		static const luaL_Reg metamethods[]; \
	}; \
	typedef LuaBinder<CLASS##LuaInfos> BINDER


#define LUA_BINDER_IMPL(CLASS, METHODS) \
	const char* CLASS##LuaInfos::className = #CLASS; \
	const luaL_Reg* CLASS##LuaInfos::methods = METHODS; \
	const luaL_Reg CLASS##LuaInfos::metamethods[] = { {NULL, NULL} }

#endif // CL_LUA_UTILS_H_INCLUDED
