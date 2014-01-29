#include "lua_ieditor.h"
#include "lua_utils.hpp"

static int lua_IEditor_GetEditorText(lua_State* L)
{
	IEditor* editor = LuaIEditor::check(L, 1);
	wxString content = editor->GetEditorText();
	lua_pushstring(L, content.c_str());
	return 1;
}

static int lua_IEditor_SetEditorText(lua_State* L)
{
	IEditor* editor = LuaIEditor::check(L, 1);
	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* content = lua_tostring(L, 2);
	editor->SetEditorText(content);
	return 0;
}

static int lua_IEditor_GetSelection(lua_State* L)
{
	IEditor* editor = LuaIEditor::check(L, 1);
	wxString selection = editor->GetSelection();
	lua_pushstring(L, selection.c_str());
	return 1;
}

static int lua_IEditor_ReplaceSelection(lua_State* L)
{
	IEditor* editor = LuaIEditor::check(L, 1);
	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* text = lua_tostring(L, 2);
	editor->ReplaceSelection(text);
	return 0;
}

static int lua_IEditor_AppendText(lua_State* L)
{
	IEditor* editor = LuaIEditor::check(L, 1);
	if (lua_isstring(L, 2) == 0)
	{
		return 0;
	}
	const char* text = lua_tostring(L, 2);
	editor->AppendText(text);
	return 0;
}

const char* IEditorLuaInfos::className = "luaL_IEditor";

const luaL_Reg IEditorLuaInfos::methods[] = {
	{"GetEditorText", lua_IEditor_GetEditorText},
	{"SetEditorText", lua_IEditor_SetEditorText},
	{"GetSelection", lua_IEditor_GetSelection},
	{"ReplaceSelection", lua_IEditor_ReplaceSelection},
	{"AppendText", lua_IEditor_AppendText},
	{NULL, NULL}
};

const luaL_Reg IEditorLuaInfos::metamethods[] = {
	{NULL, NULL}
};

const size_t IEditorLuaInfos::nMethods = METHODS_COUNT(IEditorLuaInfos::methods);
