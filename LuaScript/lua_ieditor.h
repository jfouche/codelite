#ifndef CL_LUA_IEDITOR_H_INCLUDED
#define CL_LUA_IEDITOR_H_INCLUDED

#include "lua_utils.hpp"
#include <ieditor.h>

struct IEditorLuaInfos
{
	typedef IEditor value_type;
	
	static const char* className;
	static const luaL_Reg metamethods[];
	static const luaL_Reg methods[];
	static const size_t nMethods;
};

typedef LuaBinder<IEditorLuaInfos> LuaIEditor;

#endif // CL_LUA_IEDITOR_H_INCLUDED
