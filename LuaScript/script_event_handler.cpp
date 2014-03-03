#include "script_event_handler.h"
#include "event_notifier.h"

ScriptEventHandler* ScriptEventHandler::INSTANCE = 0;

ScriptEventHandler::ScriptEventHandler(ScriptMgrPtr scriptMgr)
: m_scriptMgr(scriptMgr)
{
}

ScriptEventHandler::~ScriptEventHandler()
{
}

ScriptEventHandler* ScriptEventHandler::Get()
{
	return INSTANCE;
}

void ScriptEventHandler::Create(ScriptMgrPtr scriptMgr)
{
	if (INSTANCE == 0)
	{
		INSTANCE = new ScriptEventHandler(scriptMgr);
	}
}

void ScriptEventHandler::ConnectCmdEvent(int id)
{
	EventNotifier::Get()->Connect(id, wxCommandEventHandler(ScriptEventHandler::OnCmdEvent), NULL, this);
}

void ScriptEventHandler::OnClEvent(clCommandEvent& event)
{
	m_scriptMgr->OnClEvent(event);
}

void ScriptEventHandler::OnCmdEvent(wxCommandEvent& event)
{
	m_scriptMgr->OnCmdEvent(event);
}
