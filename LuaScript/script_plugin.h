#ifndef CL_LUA_PLUGIN_H_INCLUDED
#define CL_LUA_PLUGIN_H_INCLUDED

#include "plugin.h"
#include "script_panel.h"
#include "script_manager.h"
#include "lua_runner.h"

class wxComboBox;

class ScriptPlugin : public IPlugin
{
	static ScriptPlugin* thePlugin;
	
	ScriptManager m_scriptMgr;
	HookRunner m_hookRunner;
	ScriptPanel* m_scriptPanel;
	
public:
	ScriptPlugin(IManager* manager);
	~ScriptPlugin();
	
	static ScriptPlugin* Create(IManager* manager);
	static ScriptPlugin* Get();

	//--------------------------------------------
	//Abstract methods
	//--------------------------------------------
	virtual clToolBar *CreateToolBar(wxWindow *parent);
	virtual void CreatePluginMenu(wxMenu *pluginsMenu);
	virtual void HookPopupMenu(wxMenu *menu, MenuType type);
	virtual void UnHookPopupMenu(wxMenu *menu, MenuType type);
	virtual void UnPlug();
	
private:
	void InitUi();
	void InitHooks();
	bool IsPaneDetached() const;
	
	void onCmdEvent(wxCommandEvent& event);
	void onClEvent(clCommandEvent& event);
};

#endif // CL_LUA_PLUGIN_H_INCLUDED
