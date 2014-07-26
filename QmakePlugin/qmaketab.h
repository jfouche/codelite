//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 The CodeLite Team
// file name            : qmaketab.h
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

#ifndef __qmaketab__
#define __qmaketab__

/**
@file
Subclass of QMakeTabBase, which is generated by wxFormBuilder.
*/

#include "qmaketabbase.h"
#include "qmakeconf.h"
class IManager;

/** Implementing QMakeTabBase */
class QMakeTab : public QMakeTabBase
{
	QmakeConf *m_conf;

	void OnUseQmake(wxUpdateUIEvent &e);
public:
	/** Constructor */
	QMakeTab( wxWindow* parent, QmakeConf *conf );
	void Load(IManager* manager, const wxString &projectName, const wxString &confgName);
	void Save(IManager *manager, const wxString& projectName, const wxString& confgName);
};

#endif // __qmaketab__
