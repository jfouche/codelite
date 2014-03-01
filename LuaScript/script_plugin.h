#ifndef CL_LUA_PLUGIN_H_INCLUDED
#define CL_LUA_PLUGIN_H_INCLUDED

#include "plugin.h"
#include "script_manager.h"
#include "lua_runner.h"
#include <wx/minifram.h>

class ScriptFrame;

class ScriptPlugin : public IPlugin
{
	static ScriptPlugin* thePlugin;
	
	ScriptMgrPtr m_scriptMgr;
	HookRunner m_hookRunner;
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
	void InitHooks();
	
	void onCmdEvent(wxCommandEvent& event);
	void onClEvent(clCommandEvent& event);

	void OnShowFrame(wxCommandEvent& event);
	void OnSettings(wxCommandEvent& event);
	void OnShowFrameUi(wxUpdateUIEvent& event);
};

#endif // CL_LUA_PLUGIN_H_INCLUDED
