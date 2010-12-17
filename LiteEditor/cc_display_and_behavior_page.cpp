#include "cc_display_and_behavior_page.h"

CCDisplayAndBehvior::CCDisplayAndBehvior( wxWindow* parent, const TagsOptionsData &data  )
	: CCDisplayAndBehaviorBase( parent )
{
	m_checkDisplayFunctionTip->SetValue            (data.GetFlags() & CC_DISP_FUNC_CALLTIP ? true : false);
	m_checkDisplayTypeInfo->SetValue               (data.GetFlags() & CC_DISP_TYPE_INFO ? true : false);
	m_checkCppKeywordAssist->SetValue              (data.GetFlags() & CC_CPP_KEYWORD_ASISST ? true : false);
	m_checkDisableParseOnSave->SetValue            (data.GetFlags() & CC_DISABLE_AUTO_PARSING ? true : false);
	m_checkBoxMarkTagsFilesInBold->SetValue        (data.GetFlags() & CC_MARK_TAGS_FILES_IN_BOLD ? true : false);
	m_checkBoxretagWorkspaceOnStartup->SetValue    (data.GetFlags() & CC_RETAG_WORKSPACE_ON_STARTUP ? true : false);
	m_checkBoxDeepUsingNamespaceResolving->SetValue(data.GetFlags() & CC_DEEP_SCAN_USING_NAMESPACE_RESOLVING ? true : false);
}

void CCDisplayAndBehvior::Save(TagsOptionsData& data)
{
	SetFlag(data, CC_DISP_FUNC_CALLTIP,                   m_checkDisplayFunctionTip->IsChecked());
	SetFlag(data, CC_DISP_TYPE_INFO,                      m_checkDisplayTypeInfo->IsChecked());
	SetFlag(data, CC_CPP_KEYWORD_ASISST,                  m_checkCppKeywordAssist->IsChecked());
	SetFlag(data, CC_MARK_TAGS_FILES_IN_BOLD,             m_checkBoxMarkTagsFilesInBold->IsChecked());
	SetFlag(data, CC_RETAG_WORKSPACE_ON_STARTUP,          m_checkBoxretagWorkspaceOnStartup->IsChecked());
	SetFlag(data, CC_DEEP_SCAN_USING_NAMESPACE_RESOLVING, m_checkBoxDeepUsingNamespaceResolving->IsChecked());
	SetFlag(data, CC_DISABLE_AUTO_PARSING,                m_checkDisableParseOnSave->IsChecked());
}