#ifndef SCRIPT_FRAME_H_INCLUDED
#define SCRIPT_FRAME_H_INCLUDED

#include <wx/minifram.h>
#include "script_manager.h"

class wxListBox;

class ScriptFrame : public wxMiniFrame
{
	wxListBox* m_scripts;
	ScriptMgrPtr m_scriptMgr;

public:
	ScriptFrame(wxWindow* parent, ScriptMgrPtr scriptMgr);

	void UpdateScripts();

protected:
	void OnScriptsChanged(wxCommandEvent& event);
	void OnRunScript(wxCommandEvent& event);
};

#endif // SCRIPT_FRAME_H_INCLUDED
