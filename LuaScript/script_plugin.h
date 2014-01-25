#ifndef CL_LUA_PLUGIN_H_INCLUDED
#define CL_LUA_PLUGIN_H_INCLUDED

#include "plugin.h"
#include "script_panel.h"
#include "script_manager.h"

class wxComboBox;

class LuaPlugin : public IPlugin
{
	ScriptManager m_scriptMgr;
	ScriptPanel* m_scriptPanel;
	wxComboBox* m_combo;
	
public:
	LuaPlugin(IManager *manager);
	~LuaPlugin();

	//--------------------------------------------
	//Abstract methods
	//--------------------------------------------
	virtual clToolBar *CreateToolBar(wxWindow *parent);
	virtual void CreatePluginMenu(wxMenu *pluginsMenu);
	virtual void HookPopupMenu(wxMenu *menu, MenuType type);
	virtual void UnHookPopupMenu(wxMenu *menu, MenuType type);
	virtual void UnPlug();

private:
	void Initialize();
	bool IsPaneDetached() const;
	void OnRun(wxCommandEvent& event);
};

#endif // CL_LUA_PLUGIN_H_INCLUDED
