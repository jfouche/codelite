#include "lua_event_handler.h"

LuaEventHandler* LuaEventHandler::INSTANCE = 0;

LuaEventHandler::LuaEventHandler(LuaRunner& runner)
: m_runner(runner)
{
}

LuaEventHandler::~LuaEventHandler()
{
}

LuaEventHandler* LuaEventHandler::Get()
{
	return INSTANCE;
}

void LuaEventHandler::Init(LuaRunner& runner)
{
	if (INSTANCE == 0)
	{
		INSTANCE = new LuaEventHandler(runner);
	}
}

void LuaEventHandler::onClEvent(clCommandEvent& event)
{
}

void LuaEventHandler::onCmdEvent(wxCommandEvent& event)
{
	wxLogError("onCmdEvent");
}
