#include "script_plugin.h"
#include <wx/xrc/xmlres.h>
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "script_settings_dlg.h"
#include "script_frame.h"

#include "resources/script_gear_16.xpm"
#include "resources/script_gear_24.xpm"
#include "resources/script_lightning_16.xpm"
#include "resources/script_lightning_24.xpm"

static ScriptPlugin* thePlugin = 0;

static const int SHOW_FRAME_ID = XRCID("script_show_frame");
static const int SETTINGS_ID   = XRCID("script_settings");

// ============================================================================

//Define the plugin entry point
extern "C" EXPORT IPlugin* CreatePlugin(IManager *manager)
{
	if (thePlugin == 0)
	{
		thePlugin = new ScriptPlugin(manager);
	}
	return thePlugin;
}

extern "C" EXPORT PluginInfo GetPluginInfo()
{
	PluginInfo info;
	info.SetAuthor("J\xe9r\xe9mie Fouch\xe9");
	info.SetName("LuaScript");
	info.SetDescription("Lua bindings for CodeLite API");
	info.SetVersion("v1.0");
	return info;
}

extern "C" EXPORT int GetPluginInterfaceVersion()
{
	return PLUGIN_INTERFACE_VERSION;
}

// ============================================================================

ScriptPlugin::ScriptPlugin(IManager *manager)
	: IPlugin(manager)
	, m_scriptMgr(new ScriptManager(manager))
{
	m_longName = wxT("Lua CodeLite bindings");
	m_shortName = wxT("LuaScript");

	InitUi();
}

ScriptPlugin::~ScriptPlugin()
{
	m_scriptsFrame->Destroy();
}

clToolBar *ScriptPlugin::CreateToolBar(wxWindow *parent)
{
    clToolBar *tb = NULL;
    if (m_mgr->AllowToolbar()) 
	{
		//support both toolbars icon size
		int size = m_mgr->GetToolbarIconSize();

       tb = new clToolBar(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, clTB_DEFAULT_STYLE);
       tb->SetToolBitmapSize(wxSize(size, size));

		const char** xpmShowScript = script_lightning_16_xpm;
		const char** xpmConfScript = script_gear_16_xpm;
		if (size == 24)
		{
			xpmShowScript = script_lightning_24_xpm;
			xpmConfScript = script_gear_24_xpm;
		}
		tb->AddTool(SHOW_FRAME_ID, _("Show scripts"),     wxBitmap(xpmShowScript), _("Show scripts"),    wxITEM_CHECK);
		tb->AddTool(SETTINGS_ID,   _("Scripts settings"), wxBitmap(xpmConfScript), _("Scripts settings"));

       tb->Realize();

		// Command events
		wxTheApp->Connect(SHOW_FRAME_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ScriptPlugin::OnShowFrame), NULL, this);
		wxTheApp->Connect(SETTINGS_ID,   wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ScriptPlugin::OnSettings),  NULL, this);

		// UI events
		wxTheApp->Connect(SHOW_FRAME_ID, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptPlugin::OnShowFrameUi), NULL, this);
    }
    return tb;
}

void ScriptPlugin::CreatePluginMenu(wxMenu *pluginsMenu)
{
}

void ScriptPlugin::HookPopupMenu(wxMenu *menu, MenuType type)
{
}

void ScriptPlugin::UnHookPopupMenu(wxMenu *menu, MenuType type)
{
}

void ScriptPlugin::UnPlug()
{
		wxTheApp->Disconnect(SHOW_FRAME_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ScriptPlugin::OnShowFrame), NULL, this);
		wxTheApp->Disconnect(SETTINGS_ID,   wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ScriptPlugin::OnSettings),  NULL, this);
		wxTheApp->Disconnect(SHOW_FRAME_ID, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptPlugin::OnShowFrameUi), NULL, this);
}

void ScriptPlugin::InitUi()
{
	// Create the mini frame
	m_scriptsFrame	 = new ScriptFrame(wxTheApp->GetTopWindow(), m_scriptMgr);
}

void ScriptPlugin::OnCmdEvent(wxCommandEvent& event)
{
	m_scriptMgr->OnCmdEvent(event);
}

void ScriptPlugin::OnShowFrame(wxCommandEvent& event)
{
	m_scriptsFrame->Show(event.IsChecked());
}

void ScriptPlugin::OnSettings(wxCommandEvent& event)
{
	ScriptSettingsDialog dlg(wxTheApp->GetTopWindow(), m_scriptMgr);
	dlg.ShowModal();
}

void ScriptPlugin::OnShowFrameUi(wxUpdateUIEvent& event)
{
	bool doCheck = m_scriptsFrame->IsShown();
	if (event.GetChecked() ^ doCheck)
	{
		event.Check(doCheck);
	}
}
