#include "lua_runner.h"
#include "lua_cl_bindings.h"
#include <wx/msgdlg.h>
#include <wx/log.h>


static int cl_panic(lua_State *L)
{
	::wxMessageBox(lua_tostring(L, -1), "Lua plugin error", wxOK|wxICON_ERROR);
	CL_LUA_THROW;
}


LuaRunner::LuaRunner(IManager* manager)
: m_manager(manager)
{
	m_lua = luaL_newstate();
	lua_atpanic(m_lua, cl_panic);
	Init();
}

LuaRunner::~LuaRunner()
{
	lua_close(m_lua);
}

void LuaRunner::Init()
{
	luaL_openlibs(m_lua);

	lua_open_IManager(m_lua);
	lua_open_IEditor(m_lua);
	lua_open_Workspace(m_lua);
	lua_open_Project(m_lua);
	lua_open_Events(m_lua);

	lua_open_Codelite(m_lua, m_manager, "codelite");
}

void LuaRunner::Run(const wxString& script)
{
	wxLogMessage("[LUA] running %s", script.c_str());

	CL_LUA_TRY
	{
		int status = luaL_dofile(m_lua, script.c_str());
		if (status != LUA_OK)
		{
			const char* err = lua_tostring(m_lua, -1);
			wxString msg = wxString::Format("Error %d : %s", status, err);
			wxLogMessage("[LUA] : %s", msg.c_str());
			::wxMessageBox(msg, "Lua plugin error", wxOK|wxICON_ERROR);
			return;
		}
		wxLogMessage("[LUA] finished");
	}
}

// =============================================================================

HookRunner::HookRunner(IManager* manager)
: LuaRunner(manager)
{
}

void HookRunner::PushOnEventFunctionAndSelf()
{
	lua_getglobal(m_lua, "codelite");
	lua_getfield(m_lua, -1, "OnEvent");
	lua_pushvalue(m_lua, -2); // push self
	lua_remove(m_lua, -3);
}

void HookRunner::OnClEvent(clCommandEvent& event)
{
	RunFunctions(event.GetEventType(), &event);
}

void HookRunner::OnCmdEvent(wxCommandEvent& event)
{
	RunFunctions(event.GetEventType(), &event);
}
