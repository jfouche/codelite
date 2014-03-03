#include "lua_event_handler.h"
#include "event_notifier.h"

LuaEventHandler* LuaEventHandler::INSTANCE = 0;

LuaEventHandler::LuaEventHandler(ScriptMgrPtr scriptMgr)
: m_scriptMgr(scriptMgr)
{
}

LuaEventHandler::~LuaEventHandler()
{
}

LuaEventHandler* LuaEventHandler::Get()
{
	return INSTANCE;
}

void LuaEventHandler::Create(ScriptMgrPtr scriptMgr)
{
	if (INSTANCE == 0)
	{
		INSTANCE = new LuaEventHandler(scriptMgr);
	}
}

void LuaEventHandler::ConnectCmdEvent(int id)
{
	EventNotifier::Get()->Connect(id, wxCommandEventHandler(LuaEventHandler::OnCmdEvent), NULL, this);
}

void LuaEventHandler::OnClEvent(clCommandEvent& event)
{
	m_scriptMgr->OnClEvent(event);
}

void LuaEventHandler::OnCmdEvent(wxCommandEvent& event)
{
	m_scriptMgr->OnCmdEvent(event);
}
