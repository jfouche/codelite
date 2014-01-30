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

	/**
	 * get and pop the user data
	 */
	static value_type* get(lua_State* L, int n)
	{
		value_type* value = check(L, n);
		lua_pop(L, n);
		return value;
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
		lua_createtable(L, 0, T::nMethods);
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

#define LUA_IMPL_N_METHODS(clazz) \
    const size_t clazz::nMethods = sizeof(clazz::methods) / sizeof(*clazz::methods) - 1;

#endif // CL_LUA_UTILS_H_INCLUDED
