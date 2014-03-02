#include "lua_utils.hpp"
#include <sstream>

std::string lua::stack_dump(lua_State *L)
{
	std::ostringstream oss;
	oss << "Lua stack ( " << L << ")" << std::endl;
	const int top = lua_gettop(L);
	for (int i = 1; i <= top; i++)    /* repeat for each level */
	{
		oss << " - " << i << " : ";
		const int t = lua_type(L, i);
		switch (t)
		{
		case LUA_TSTRING:  /* strings */
			oss << '"' << lua_tostring(L, i) << '"';
			break;

		case LUA_TBOOLEAN:  /* booleans */
			oss << (lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			oss << lua_tonumber(L, i);
			break;

		default:  /* other values */
			oss << lua_typename(L, t);
			break;
		}
		oss << std::endl;  /* put a separator */
	}
	return oss.str();
}

void lua::print_stack(lua_State *L)
{
	printf(stack_dump(L).c_str());
	printf("\n");
	fflush(stdout);
}

void lua::createClass(lua_State* L, const char* name)
{
	luaL_newmetatable(L, name); // New metatable on the stack
	lua_pushvalue(L, -1); // there are two 'copies' of the metatable on the stack
	lua_setfield(L, -2, "__index");
}

void lua::createClass(lua_State* L, const char* name, const luaL_Reg* methods)
{
	createClass(L, name);
	luaL_setfuncs(L, methods, 0);
}

const char* lua::check_string(lua_State* L, int n, const char* error)
{
	if (!lua_isstring(L, n))
	{
		luaL_error(L, error ? error : "Expected string");
	}
	return lua_tostring(L, n);
}

LUA_NUMBER lua::check_integer(lua_State* L, int n, const char* error)
{
	if (!lua_isnumber(L, n))
	{
		luaL_error(L, error ? error : "Expected integer");
	}
	return lua_tointeger(L, n);
}

void lua::check_table(lua_State* L, int n, const char* error)
{
	if (!lua_istable(L, n))
	{
		luaL_error(L, error ? error : "Expected table");
	}
}

void lua::check_function(lua_State* L, int n, const char* error)
{
	if (!lua_isfunction(L, n))
	{
		luaL_error(L, error ? error : "Expected function");
	}
}
