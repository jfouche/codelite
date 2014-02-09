#include "lua_utils.hpp"
#include "ieditor.h"

static const char* CLASSNAME = "IEditor";

namespace lua
{
	template <>
	void push(lua_State* L, IEditor* instance)
	{
		push(L, instance, CLASSNAME);
	}

	template <>
	IEditor* check(lua_State* L, int n)
	{
		return check<IEditor>(L, n, CLASSNAME);
	}
}

/// @lua IEditor.GetEditorText() : return string
static int GetEditorText(lua_State* L)
{
	IEditor* editor = lua::check<IEditor>(L, 1);
	wxString content = editor->GetEditorText();
	lua_pushstring(L, content.c_str());
	return 1;
}

/// @lua IEditor.SetEditorText(string)
static int SetEditorText(lua_State* L)
{
	IEditor* editor = lua::check<IEditor>(L, 1);
	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* content = lua_tostring(L, 2);
	editor->SetEditorText(content);
	return 0;
}

/// @lua IEditor.GetSelection() : return string
static int GetSelection(lua_State* L)
{
	IEditor* editor = lua::check<IEditor>(L, 1);
	wxString selection = editor->GetSelection();
	lua_pushstring(L, selection.c_str());
	return 1;
}

/// @lua IEditor.ReplaceSelection(string)
static int ReplaceSelection(lua_State* L)
{
	IEditor* editor = lua::check<IEditor>(L, 1);
	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* text = lua_tostring(L, 2);
	editor->ReplaceSelection(text);
	return 0;
}

/// @lua IEditor.AppendText(string)
static int AppendText(lua_State* L)
{
	IEditor* editor = lua::check<IEditor>(L, 1);
	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* text = lua_tostring(L, 2);
	editor->AppendText(text);
	return 0;
}

static const luaL_Reg METHODS[] = {
	{"GetEditorText", GetEditorText},
	{"SetEditorText", SetEditorText},
	{"GetSelection", GetSelection},
	{"ReplaceSelection", ReplaceSelection},
	{"AppendText", AppendText},
	{NULL, NULL}
};

void lua_open_IEditor(lua_State* L)
{
	luaL_newmetatable(L, CLASSNAME);
	lua_createtable(L, 0, 0);
	luaL_setfuncs(L, METHODS, 0);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}
