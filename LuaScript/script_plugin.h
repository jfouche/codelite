#ifndef CL_LUA_PLUGIN_H_INCLUDED
#define CL_LUA_PLUGIN_H_INCLUDED

#include "plugin.h"
#include "script_manager.h"
#include "lua_runner.h"

class ScriptFrame;

class ScriptPlugin : public IPlugin
{
	static ScriptPlugin* thePlugin;
	
	ScriptMgrPtr m_scriptMgr;
	ScriptFrame* m_scriptsFrame;
	
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
	
	void OnCmdEvent(wxCommandEvent& event);
	void OnClEvent(clCommandEvent& event);

	void OnShowFrame(wxCommandEvent& event);
	void OnSettings(wxCommandEvent& event);
	void OnShowFrameUi(wxUpdateUIEvent& event);
};

#endif // CL_LUA_PLUGIN_H_INCLUDED
