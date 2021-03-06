//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2009 by Eran Ifrah
// file name            : svnblameeditor.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef SVNBLAMEEDITOR_H
#define SVNBLAMEEDITOR_H

#include <wx/stc/stc.h>
#include <vector>

struct BlameLineInfo {
	wxString revision;
	int      style;
};

class SvnBlameEditor : public wxStyledTextCtrl {
	std::vector<BlameLineInfo> m_lineInfo;
	int                        m_lineNumber;
protected:
	void Initialize();

public:
	SvnBlameEditor(wxWindow *win);
	virtual ~SvnBlameEditor();

	void SetText(const wxString &text);

	DECLARE_EVENT_TABLE()
	void OnContextMenu      (wxContextMenuEvent &event);
	void OnHighlightRevision(wxCommandEvent &event);
};

#endif // SVNBLAMEEDITOR_H
