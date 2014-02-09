#ifndef CL_LUA_UTILS_H_INCLUDED
#define CL_LUA_UTILS_H_INCLUDED

#include <lua.hpp>
#include <string>

namespace lua
{
	template <typename T>
	void push(lua_State* L, T* instance, const char* name)
	{
		T** udata = static_cast<T**>(lua_newuserdata(L, sizeof(void*)));
		*udata = instance;
		luaL_getmetatable(L, name);
		lua_setmetatable(L, -2);
	}

	/// To be specialized
	template <typename T>
	void push(lua_State* L, T* instance);

	template <typename T>
	T* check(lua_State* L, int n, const char* name)
	{
		return *(T**) luaL_checkudata(L, n, name);
	}
	
	/// To be specialized
	template <typename T>
	T* check(lua_State* L, int n);

	std::string stack_dump(lua_State *L);
	
	void print_stack(lua_State *L);
}

#endif // CL_LUA_UTILS_H_INCLUDED
