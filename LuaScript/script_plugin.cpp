#include "script_plugin.h"
#include <wx/xrc/xmlres.h>
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "script_settings_dlg.h"
#include "script_frame.h"

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
	info.SetAuthor("Jérémie Fouché");
	info.SetName("Lua");
	info.SetDescription("Lua script");
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
	m_longName = wxT("Lua script plugin");
	m_shortName = wxT("Lua");

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

		wxString bmpShowScript = "script_lightning_16.png";
		wxString bmpConfScript = "script_gear_16.png";
		if (size == 24)
		{
			bmpShowScript = "script_lightning_24.png";
			bmpConfScript = "script_gear_24.png";
		}
		tb->AddTool(SHOW_FRAME_ID, _("Show scripts"),     LoadBitmapFile(bmpShowScript), _("Show scripts"),    wxITEM_CHECK);
		tb->AddTool(SETTINGS_ID,   _("Scripts settings"), LoadBitmapFile(bmpConfScript), _("Scripts settings"));

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
	/*
		// You can use the below code a snippet:
	 	wxMenu *menu = new wxMenu();
		wxMenuItem *item(NULL);
		item = new wxMenuItem(menu, XRCID("new_plugin"), _("New CodeLite Plugin Wizard..."), wxEmptyString, wxITEM_NORMAL);
		menu->Append(item);
		item = new wxMenuItem(menu, XRCID("new_class"), _("New Class Wizard..."), wxEmptyString, wxITEM_NORMAL);
		menu->Append(item);
		item = new wxMenuItem(menu, XRCID("new_wx_project"), _("New wxWidgets Project Wizard..."), wxEmptyString, wxITEM_NORMAL);
		menu->Append(item);
		pluginsMenu->Append(wxID_ANY, _("Gizmos"), menu);
	*/
}

void ScriptPlugin::HookPopupMenu(wxMenu *menu, MenuType type)
{
}

void ScriptPlugin::UnHookPopupMenu(wxMenu *menu, MenuType type)
{
}

void ScriptPlugin::UnPlug()
{
}

void ScriptPlugin::InitUi()
{
	// Create the mini frame
	m_scriptsFrame	 = new ScriptFrame(wxTheApp->GetTopWindow(), m_scriptMgr);
}

void ScriptPlugin::OnClEvent(clCommandEvent& event)
{
	m_scriptMgr->OnClEvent(event);
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
