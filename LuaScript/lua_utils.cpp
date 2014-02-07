#include "lua_utils.hpp"
#include <sstream>

std::string lua::stack_dump(lua_State *L)
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
			oss << (lua_toboolean(L, i) ? "true" : "false");
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
