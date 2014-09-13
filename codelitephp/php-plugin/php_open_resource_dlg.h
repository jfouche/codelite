#ifndef __php_open_resource_dlg__
#define __php_open_resource_dlg__

/**
@file
Subclass of OpenResourceDlgBase, which is generated by wxFormBuilder.
*/

#include "php_ui.h"
#include "php_storage.h"

//// end generated include
/** Implementing OpenResourceDlgBase */
class IManager;
class OpenResourceDlg : public OpenResourceDlgBase
{
public:

    wxString       m_lastFilter;
    IManager *     m_mgr;
    wxTimer *      m_timer;
    ResourceVector_t m_allFiles;
    ResourceVector_t m_resources;
    ResourceItem*  m_selectedItem;

protected:
    virtual void OnDVItemActivated(wxDataViewEvent& event);

    ResourceVector_t DoGetFiles(const wxString &filter);
    void DoGetResources(const wxString &filter);
    ResourceItem*  DoGetItemData(const wxDataViewItem& item);
    wxBitmap       DoGetImgIdx(const ResourceItem* item);

protected:
    void DoSelectNext();
    void DoSelectPrev();
    void DoInitialize();
    void DoPopulateListCtrl(const ResourceVector_t& items);

protected:
    // Handlers for OpenResourceDlgBase events.
    void OnFilterEnter(wxCommandEvent& event);
    void OnFilterText(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);

    DECLARE_EVENT_TABLE()
    void OnTimer(wxTimerEvent &event);

public:
    /** Constructor */
    OpenResourceDlg( wxWindow* parent, IManager *manager );
    OpenResourceDlg( wxWindow* parent, const ResourceVector_t &items, IManager* manager );
    virtual ~OpenResourceDlg();

    void SetSelectedItem(ResourceItem* selectedItem) {
        this->m_selectedItem = selectedItem;
    }
    ResourceItem* GetSelectedItem() {
        return m_selectedItem;
    }
};

#endif // __php_open_resource_dlg__
