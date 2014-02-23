#include "script_plugin.h"
#include <wx/xrc/xmlres.h>
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "event_notifier.h"

ScriptPlugin* ScriptPlugin::thePlugin = 0;

static const char* SCRIPT_PANE_TITLE = "Scripts";

static const int SHOW_FRAME_ID = XRCID("script_show_frame");
static const int SETTINGS_ID   = XRCID("script_settings");

// ============================================================================

class ScriptFrame : public wxMiniFrame
{
	wxListBox* m_scripts;
	ScriptMgrPtr m_scriptMgr;

public:
	ScriptFrame(wxWindow* parent, ScriptMgrPtr scriptMgr);

	void UpdateScripts();

protected:
	void OnRunScript(wxCommandEvent& event);
};

ScriptFrame::ScriptFrame(wxWindow* parent, ScriptMgrPtr scriptMgr)
: wxMiniFrame(parent, wxID_ANY, _("Scripts"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxRESIZE_BORDER|wxSTAY_ON_TOP)
, m_scriptMgr(scriptMgr)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);
	
	m_scripts = new wxListBox(this, wxID_ANY);
	sizer->Add(m_scripts, 1, wxALL|wxEXPAND, 0);
	
	SetSizeHints(200,300);
	sizer->Fit(this);
	
	SetTransparent(210);
	
    m_scripts->Connect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(ScriptFrame::OnRunScript), NULL, this);
	UpdateScripts();

	Show(false);
}

void ScriptFrame::UpdateScripts()
{
	wxArrayString scripts;
	m_scriptMgr->GetScripts(scripts);
	m_scripts->Set(scripts);
}

void ScriptFrame::OnRunScript(wxCommandEvent& event)
{
	wxString script = m_scripts->GetStringSelection();
	if (script.IsEmpty() == false)
	{
		m_scriptMgr->RunScript(script);
	}
}

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
	, m_hookRunner(manager)
{
	m_longName = wxT("Lua script plugin");
	m_shortName = wxT("Lua");

	InitHooks();
	InitUi();
	
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
	wxLogMessage("ScriptPlugin::InitUi");
	
	
	// Create the mini frame
	m_scriptsFrame	 = new ScriptFrame(wxTheApp->GetTopWindow(), m_scriptMgr);
	
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
	m_scriptMgr->GetHooks(hooks);
	
	for (size_t i = 0; i < hooks.size(); ++i)
	{
		wxString hook = m_scriptMgr->GetHookPath(hooks[i]);
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
	m_hookRunner.onClEvent(event);
}

void ScriptPlugin::onCmdEvent(wxCommandEvent& event)
{
	m_hookRunner.onCmdEvent(event);
}

void ScriptPlugin::OnShowFrame(wxCommandEvent& event)
{
	m_scriptsFrame->Show(event.IsChecked());
}

void ScriptPlugin::OnSettings(wxCommandEvent& event)
{
	
}

void ScriptPlugin::OnShowFrameUi(wxUpdateUIEvent& event)
{
	bool doCheck = m_scriptsFrame->IsShown();
	if (event.GetChecked() ^ doCheck)
	{
		event.Check(doCheck);
	}
}
