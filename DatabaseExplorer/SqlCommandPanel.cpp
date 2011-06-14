
#include "DbViewerPanel.h"
#include <wx/file.h>
#include <wx/textfile.h>
#include "SqlCommandPanel.h"
#include <wx/wupdlock.h>
#include <wx/busyinfo.h>
#include <wx/xrc/xmlres.h>
#include "globals.h"


const wxEventType wxEVT_EXECUTE_SQL = XRCID("wxEVT_EXECUTE_SQL");

BEGIN_EVENT_TABLE(SQLCommandPanel, _SqlCommandPanel)
	EVT_COMMAND(wxID_ANY, wxEVT_EXECUTE_SQL, SQLCommandPanel::OnExecuteSQL)
END_EVENT_TABLE()

SQLCommandPanel::SQLCommandPanel(wxWindow *parent,IDbAdapter* dbAdapter,  const wxString& dbName, const wxString& dbTable)
	: _SqlCommandPanel(parent)
{
	DbViewerPanel::InitStyledTextCtrl( m_scintillaSQL );
	m_pDbAdapter = dbAdapter;
	m_dbName = dbName;
	m_dbTable = dbTable;
	
	wxTheApp->Connect(wxID_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Connect(wxID_COPY,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Connect(wxID_PASTE,     wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Connect(wxID_CUT,       wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Connect(wxID_UNDO,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Connect(wxID_REDO,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	
	wxTheApp->Connect(wxID_SELECTALL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Connect(wxID_COPY,      wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Connect(wxID_PASTE,     wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Connect(wxID_CUT,       wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Connect(wxID_UNDO,      wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Connect(wxID_REDO,      wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	
	
	m_scintillaSQL->AddText(wxString::Format(wxT(" -- selected database %s\n"), m_dbName.c_str()));
	if (!dbTable.IsEmpty()) {
		m_scintillaSQL->AddText(m_pDbAdapter->GetDefaultSelect(m_dbName, m_dbTable));
		wxCommandEvent event(wxEVT_EXECUTE_SQL);
		GetEventHandler()->AddPendingEvent(event);
	}
}

SQLCommandPanel::~SQLCommandPanel()
{
	wxTheApp->Disconnect(wxID_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Disconnect(wxID_COPY,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Disconnect(wxID_PASTE,     wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Disconnect(wxID_CUT,       wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Disconnect(wxID_UNDO,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	wxTheApp->Disconnect(wxID_REDO,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SQLCommandPanel::OnEdit),   NULL, this);
	
	wxTheApp->Disconnect(wxID_SELECTALL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Disconnect(wxID_COPY,      wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Disconnect(wxID_PASTE,     wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Disconnect(wxID_CUT,       wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Disconnect(wxID_UNDO,      wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	wxTheApp->Disconnect(wxID_REDO,      wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SQLCommandPanel::OnEditUI),   NULL, this);
	
	delete m_pDbAdapter;
}

void SQLCommandPanel::OnExecuteClick(wxCommandEvent& event)
{
	event.Skip();
	ExecuteSql();
}

void SQLCommandPanel::OnScintilaKeyDown(wxKeyEvent& event)
{
	if ((event.ControlDown())&&(event.GetKeyCode() == WXK_RETURN)) {
		ExecuteSql();
	}
	event.Skip();
}

void SQLCommandPanel::ExecuteSql()
{
	wxBusyInfo infoDlg(_("Executing sql..."), wxTheApp->GetTopWindow());
	wxTheApp->Yield();
	
	wxWindowUpdateLocker locker(this);
	DatabaseLayer* m_pDbLayer = m_pDbAdapter->GetDatabaseLayer(m_dbName);
	if (m_pDbLayer->IsOpen()) {
		// test for empty string
		if (this->m_scintillaSQL->GetText() != wxT("")) {
			try {
				if (!m_pDbAdapter->GetUseDb(m_dbName).IsEmpty()) m_pDbLayer->RunQuery(m_pDbAdapter->GetUseDb(m_dbName));
				// run query
				DatabaseResultSet* pResultSet = m_pDbLayer->RunQueryWithResults(this->m_scintillaSQL->GetText());
				
				// clear variables
				m_gridTable->DeleteCols(0,m_gridTable->GetNumberCols());
				m_gridTable->DeleteRows(0,m_gridTable->GetNumberRows());
				m_gridValues.clear();
				
				int rows = 0;
				int cols = pResultSet->GetMetaData()->GetColumnCount();

				// create table header
				m_gridTable->AppendCols(cols);
				for (int i = 1; i<= pResultSet->GetMetaData()->GetColumnCount(); i++) {
					m_gridTable->SetColLabelValue(i-1,pResultSet->GetMetaData()->GetColumnName(i));
				}

				// fill table data
				while (pResultSet->Next()) {
					wxString value;
					m_gridTable->AppendRows();
					for (int i = 1; i<= pResultSet->GetMetaData()->GetColumnCount(); i++) {

						switch (pResultSet->GetMetaData()->GetColumnType(i)) {
						case ResultSetMetaData::COLUMN_INTEGER:
							value = wxString::Format(wxT("%i"),pResultSet->GetResultInt(i));
							break;
							
						case ResultSetMetaData::COLUMN_STRING:
							value =  pResultSet->GetResultString(i);
							break;
							
						case ResultSetMetaData::COLUMN_UNKNOWN:
							value = pResultSet->GetResultString(i);
							break;
							
						case ResultSetMetaData::COLUMN_BLOB:
						{
							wxMemoryBuffer buffer;
							pResultSet->GetResultBlob(i, buffer);
							value = wxString::Format(wxT("BLOB (Size:%u)"), buffer.GetDataLen());
							break;
						}
						case ResultSetMetaData::COLUMN_BOOL:
							value = wxString::Format(wxT("%b"),pResultSet->GetResultBool(i));
							break;
							
						case ResultSetMetaData::COLUMN_DATE:
							value = pResultSet->GetResultDate(i).Format();
							break;
							
						case ResultSetMetaData::COLUMN_DOUBLE:
							value = wxString::Format(wxT("%f"),pResultSet->GetResultDouble(i));
							break;
							
						case ResultSetMetaData::COLUMN_NULL:
							value = wxT("NULL");
							break;
							
						default:
							value = pResultSet->GetResultString(i);
							break;
						}
						
						m_gridValues[std::make_pair<int, int>(rows,  i-1)] = value;
						
						// truncate the string to a reasonable string
						if(value.Length() > 100) {
							value = value.Mid(0, 100);
							value.Append(wxT("..."));
						}
						
						// Convert all whitespace chars into visible ones
						value.Replace(wxT("\n"), wxT("\\n"));
						value.Replace(wxT("\r"), wxT("\\r"));
						value.Replace(wxT("\t"), wxT("\\t"));
						m_gridTable->SetCellValue(value ,rows, i-1);
					}
					rows++;
				}
				
				m_pDbLayer->CloseResultSet(pResultSet);
				m_gridTable->AutoSize();
				
				// show result status
				m_labelStatus->SetLabel(wxString::Format(_("Result: %i rows"),rows));
				Layout();
				
			} catch (DatabaseLayerException& e) {
				// for some reason an exception is thrown even if the error code is 0...
				if(e.GetErrorCode() != 0) {
					wxString errorMessage = wxString::Format(_("Error (%d): %s"), e.GetErrorCode(), e.GetErrorMessage().c_str());
					wxMessageDialog dlg(this,errorMessage,_("DB Error"),wxOK | wxCENTER | wxICON_ERROR);
					dlg.ShowModal();
				}
				
			} catch( ... ) {
				wxMessageDialog dlg(this,_("Unknown error."),_("DB Error"),wxOK | wxCENTER | wxICON_ERROR);
				dlg.ShowModal();
				
			}
		}

	} else
		wxMessageBox(_("Cant connect!"));
}

void SQLCommandPanel::OnLoadClick(wxCommandEvent& event)
{
	wxFileDialog dlg(this, _("Chose a file"),wxT(""),wxT(""),wxT("Sql files(*.sql)|*.sql"),wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	m_scintillaSQL->ClearAll();
	if (dlg.ShowModal() == wxID_OK) {
		wxTextFile file( dlg.GetPath());
		file.Open();
		if (file.IsOpened()) {
			for ( wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine() ) {
				m_scintillaSQL->AddText(str);
				m_scintillaSQL->AddText(wxT("\n"));
			}
		}
	}
}

void SQLCommandPanel::OnSaveClick(wxCommandEvent& event)
{
	wxFileDialog dlg(this,_("Chose a file"),wxT(""),wxT(""),wxT("Sql files(*.sql)|*.sql"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_OK) {

		wxFile file(dlg.GetPath(),wxFile::write);
		if (file.IsOpened()) {
			file.Write(m_scintillaSQL->GetText());
			file.Close();
		}
	}
}

void SQLCommandPanel::OnTeplatesLeftDown(wxMouseEvent& event)
{
}
void SQLCommandPanel::OnTemplatesBtnClick(wxCommandEvent& event)
{
	wxMenu menu;

	menu.Append(IDR_SQLCOMMAND_SELECT,_("Insert SELECT SQL template"),_("Insert SELECT SQL statement template into editor."));
	menu.Append(IDR_SQLCOMMAND_INSERT,_("Insert INSERT SQL template"),_("Insert INSERT SQL statement template into editor."));
	menu.Append(IDR_SQLCOMMAND_UPDATE,_("Insert UPDATE SQL template"),_("Insert UPDATE SQL statement template into editor."));
	menu.Append(IDR_SQLCOMMAND_DELETE,_("Insert DELETE SQL template"),_("Insert DELETE SQL statement template into editor."));
	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SQLCommandPanel::OnPopupClick, NULL, this);
	PopupMenu(&menu);
}
void SQLCommandPanel::OnPopupClick(wxCommandEvent& evt)
{

	if (evt.GetId() == IDR_SQLCOMMAND_SELECT) {
		m_scintillaSQL->AddText(wxT("SELECT * FROM TableName\n"));
	} else	if (evt.GetId() == IDR_SQLCOMMAND_INSERT) {
		m_scintillaSQL->AddText(wxT("INSERT INTO TableName (ColumnA, ColumnB) VALUES (1,'Test text')\n"));
	} else	if (evt.GetId() == IDR_SQLCOMMAND_UPDATE) {
		m_scintillaSQL->AddText(wxT("UPDATE TableName SET ColumnA = 2, ColumnB = 'Second text' WHERE ID = 1\n"));
	} else	if (evt.GetId() == IDR_SQLCOMMAND_DELETE) {
		m_scintillaSQL->AddText(wxT("DELETE FROM TableName WHERE ID = 1\n"));
	}
}

void SQLCommandPanel::OnExecuteSQL(wxCommandEvent& e)
{
	wxUnusedVar(e);
	ExecuteSql();
}

void SQLCommandPanel::OnGridCellRightClick(wxGridEvent& event)
{
	event.Skip();
	
	// Keep the current cell's value (taken from the map and NOT from the UI)
	std::map<std::pair<int, int>, wxString >::const_iterator iter = m_gridValues.find(std::make_pair<int, int>(event.GetRow(), event.GetCol()));
	if(iter == m_gridValues.end())
		return;

	m_cellValue = iter->second;
	
	wxMenu menu; 
	menu.Append (XRCID("db_copy_cell_value"), _("Copy value to clipboard"));
	menu.Connect(XRCID("db_copy_cell_value"), wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(SQLCommandPanel::OnCopyCellValue), NULL, this);
	m_gridTable->PopupMenu( &menu );
}

void SQLCommandPanel::OnCopyCellValue(wxCommandEvent& e)
{
	e.Skip();
	if(m_cellValue.IsEmpty() == false) {
		CopyToClipboard(m_cellValue);
	}
}

void SQLCommandPanel::OnEdit(wxCommandEvent& e)
{
	if(wxWindow::FindFocus() == m_scintillaSQL) {
		switch(e.GetId()) {
		case wxID_REDO:
			if(m_scintillaSQL->CanRedo()) {
				m_scintillaSQL->Redo();
			}
			break;
			
		case wxID_UNDO:
			if(m_scintillaSQL->CanUndo()) {
				m_scintillaSQL->Undo();
			}
			break;
			
		case wxID_CUT:
			if((m_scintillaSQL->GetSelectionStart() - m_scintillaSQL->GetSelectionEnd()) != 0) {
				m_scintillaSQL->Cut();
			}
			break;
		case wxID_COPY:
			if((m_scintillaSQL->GetSelectionStart() - m_scintillaSQL->GetSelectionEnd()) != 0) {
				m_scintillaSQL->Copy();
			}
			break;
		case wxID_PASTE:
			if(m_scintillaSQL->CanPaste()) {
				m_scintillaSQL->Paste();
			}
			break;
		case wxID_SELECTALL:
			m_scintillaSQL->SelectAll();
			break;
		}
	} else {
		e.Skip();
		
	}
}

void SQLCommandPanel::OnEditUI(wxUpdateUIEvent& e)
{
	if(wxWindow::FindFocus() == m_scintillaSQL) {
		bool enable = false;
		switch(e.GetId()) {
		case wxID_REDO:
			enable = m_scintillaSQL->CanRedo();
			break;
			
		case wxID_UNDO:
			enable = m_scintillaSQL->CanUndo();
			break;
			
		case wxID_COPY:
		case wxID_CUT:
			enable = ((m_scintillaSQL->GetSelectionStart() - m_scintillaSQL->GetSelectionEnd()) != 0);
			break;
		
		case wxID_PASTE:
			enable = m_scintillaSQL->CanPaste();
			break;
			
		case wxID_SELECTALL:
			enable = m_scintillaSQL->GetLength() > 0;
			break;
		default:
			break;
		}
		e.Enable(enable);
		
	} else {
		e.Skip();
		
	}
}