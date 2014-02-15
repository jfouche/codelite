#include "script_plugin.h"
#include <wx/xrc/xmlres.h>
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "event_notifier.h"

ScriptPlugin* ScriptPlugin::thePlugin = 0;

static const char* SCRIPT_PANE_TITLE = "Scripts";


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

ScriptPlugin::ScriptPlugin(IManager *manager)
	: IPlugin(manager)
	, m_scriptMgr(manager)
	, m_hookRunner(manager)
{
	m_longName = wxT("Lua script plugin");
	m_shortName = wxT("Lua");

	InitUi();
	InitHooks();
	
	EventNotifier* evSrc = EventNotifier::Get();
	evSrc->Connect(wxEVT_FILE_SAVED, wxCommandEventHandler(ScriptPlugin::onCmdEvent), NULL, this);
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
	// Create the toolbar to be used by the plugin
	clToolBar *tb(NULL);
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
// Remove the tab if it's actually docked in the workspace pane
    size_t index = m_mgr->GetWorkspacePaneNotebook()->GetPageIndex(m_scriptPanel);
    if (index != Notebook::npos) 
	{
        m_mgr->GetWorkspacePaneNotebook()->RemovePage(index, false);
    }
    m_scriptPanel->Destroy();
}

void ScriptPlugin::InitUi()
{
    // create tab (possibly detached)
    Notebook *book = m_mgr->GetWorkspacePaneNotebook();
    if( IsPaneDetached() ) 
	{
        // Make the window child of the main panel (which is the grand parent of the notebook)
		 wxWindow* gParent = book->GetParent()->GetParent();
        DockablePane* cp = new DockablePane(gParent, book, SCRIPT_PANE_TITLE, wxNullBitmap, wxSize(200, 200));
        m_scriptPanel = new ScriptPanel(cp, m_scriptMgr);
        cp->SetChildNoReparent(m_scriptPanel);
    } 
	else
	{
        m_scriptPanel = new ScriptPanel(book, m_scriptMgr);
        book->AddPage(m_scriptPanel, SCRIPT_PANE_TITLE, false);
    }
}

void ScriptPlugin::InitHooks()
{
	wxArrayString hooks;
	m_scriptMgr.GetHooks(hooks);
	
	for (size_t i = 0; i < hooks.size(); ++i)
	{
		wxString hook = m_scriptMgr.GetHookPath(hooks[i]);
		m_hookRunner.Run(hook);
	}
}

bool ScriptPlugin::IsPaneDetached() const
{
    DetachedPanesInfo dpi;
    m_mgr->GetConfigTool()->ReadObject(wxT("DetachedPanesList"), &dpi);
    wxArrayString detachedPanes = dpi.GetPanes();
    return detachedPanes.Index(SCRIPT_PANE_TITLE) != wxNOT_FOUND;
}

void ScriptPlugin::onClEvent(clCommandEvent& event)
{
	printf("OnClEvent(%d)\n", event.GetEventType());
	m_hookRunner.onClEvent(event);
}

void ScriptPlugin::onCmdEvent(wxCommandEvent& event)
{
	printf("onCmdEvent(%d)\n", event.GetEventType()); fflush(stdout);
	m_hookRunner.onCmdEvent(event);
}
