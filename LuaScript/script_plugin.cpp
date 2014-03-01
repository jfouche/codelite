#include "script_plugin.h"
#include <wx/xrc/xmlres.h>
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "event_notifier.h"
#include "script_settings_dlg.h"
#include "script_frame.h"

ScriptPlugin* ScriptPlugin::thePlugin = 0;

static const int SHOW_FRAME_ID = XRCID("script_show_frame");
static const int SETTINGS_ID   = XRCID("script_settings");

// ============================================================================

//Define the plugin entry point
extern "C" EXPORT IPlugin *CreatePlugin(IManager *manager)
{
	return ScriptPlugin::Create(manager);
}

extern "C" EXPORT PluginInfo GetPluginInfo()
{
	PluginInfo info;
	info.SetAuthor(wxT("Jérémie Fouché"));
	info.SetName(wxT("Lua"));
	info.SetDescription(wxT("Lua script"));
	info.SetVersion(wxT("v1.0"));
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
	
	EventNotifier* evSrc = EventNotifier::Get();
	evSrc->Connect(wxEVT_FILE_SAVED, wxCommandEventHandler(ScriptPlugin::OnCmdEvent), NULL, this);
}

ScriptPlugin::~ScriptPlugin()
{
}

ScriptPlugin* ScriptPlugin::Create(IManager* manager)
{
	if (thePlugin == 0)
	{
		thePlugin = new ScriptPlugin(manager);
	}
	return thePlugin;
}

ScriptPlugin* ScriptPlugin::Get()
{
	return thePlugin;
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

       // Sample code that adds single button to the toolbar
       // and associates an image to it
       if (size == 24) 
		{
            //use the large icons set
            tb->AddTool(SHOW_FRAME_ID, _("Show scripts"),     LoadBitmapFile("script_lightning.png"), _("Show scripts"),    wxITEM_CHECK);
            tb->AddTool(SETTINGS_ID,   _("Scripts settings"), LoadBitmapFile("script_gear.png"),      _("Scripts settings"));
       }
		else 
		{
            //16
            tb->AddTool(SHOW_FRAME_ID, _("Show scripts"),     LoadBitmapFile("script_lightning.png"), _("Show scripts"),    wxITEM_CHECK);
            tb->AddTool(SETTINGS_ID,   _("Scripts settings"), LoadBitmapFile("script_gear.png"),      _("Scripts settings"));
       }
       tb->Realize();
    }

    // Command events
    wxTheApp->Connect(SHOW_FRAME_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ScriptPlugin::OnShowFrame), NULL, this);
    wxTheApp->Connect(SETTINGS_ID,   wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ScriptPlugin::OnSettings),  NULL, this);

    // UI events
    wxTheApp->Connect(SHOW_FRAME_ID, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(ScriptPlugin::OnShowFrameUi), NULL, this);

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
	wxLogMessage("ScriptPlugin::InitUi");

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
