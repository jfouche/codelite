#include "lua_utils.hpp"
#include <sstream>

std::string lua_stack_dump(lua_State *L)
{
	std::ostringstream oss;
	oss << "lua stack : ";
	const int top = lua_gettop(L);
	for (int i = 1; i <= top; i++)    /* repeat for each level */
	{
		const int t = lua_type(L, i);
		switch (t)
		{
		case LUA_TSTRING:  /* strings */
			oss << '"' << lua_tostring(L, i) << '"';
			break;

		case LUA_TBOOLEAN:  /* booleans */
			oss << lua_toboolean(L, i) ? "true" : "false";
			break;

		case LUA_TNUMBER:  /* numbers */
			oss << lua_tonumber(L, i);
			break;

		default:  /* other values */
			oss << lua_typename(L, t);
			break;
		}
		oss << " ";  /* put a separator */
	}
	oss << std::endl;/* end the listing */
	return oss.str();
}

#if 0
void lua::registerClass(lua_State* L, const char* name, const luaL_Reg* methods, const luaL_Reg* metas)
{
	luaL_newmetatable(L, name);
	if (metas == NULL)
	{
		luaL_setfuncs(L, NO_METAS, 0);
	}
	else
	{
		luaL_setfuncs(L, metas, 0);
	}
	luaL_newlib(L, methods);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
	stack_dump(L);
}
#endif