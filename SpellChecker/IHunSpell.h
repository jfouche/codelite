/////////////////////////////////////////////////////////////////////////////
// Name:        IHunSpell.h
// Purpose:
// Author:      Frank Lichtner
// Modified by:
// Created:     02/02/14
// SVN-ID:      $Id: IHunSpell.h 35 2014-02-22 18:18:49Z Frank $
// Copyright:   2014 Frank Lichtner
// License:
/////////////////////////////////////////////////////////////////////////////
#ifndef _IHUNSPELL_
#define _IHUNSPELL_
// ------------------------------------------------------------
#include <hunspell/hunspell.h>
#include <wx/hashmap.h>
#include <vector>
#include <utility>
// ------------------------------------------------------------
WX_DECLARE_STRING_HASH_MAP( wxString, languageMap );
typedef std::pair<int, int>         posLen;
typedef std::pair<posLen, int>      parseEntry;
typedef std::vector<parseEntry>     partList;
// ------------------------------------------------------------
class CorrectSpellingDlg;
class SpellCheck;
class IEditor;
// ------------------------------------------------------------
class IHunSpell
{
public:

	IHunSpell();
	virtual ~IHunSpell();

	/// Clears the ignore list
	void ClearIgnoreList() { m_ignoreList.Clear(); }
	/// initializes spelling engine. This will be done automatic on the first check.
	bool InitEngine();
	/// close the engine. The engine must be closed before a new init or when the program finishes.
	void CloseEngine();
	/// changes the engines language. Must be in format like 'en_US'. No Close, Init necessary
	bool ChangeLanguage( const wxString& language );
	/// check spelling for one word. Return 0 if the word was not found, otherwise != 0.
	int CheckWord( const wxString& word );
	/// returns an array with suggestions for the misspelled word.
	wxArrayString GetSuggestions( const wxString& misspelled );
	/// makes a spell check for the given cpp text. Canceled is set to true when the user cancels.
	void CheckCppSpelling( const wxString& check );
	/// makes a spell check for the given plain text. Canceled is set to true when the user cancels.
	void CheckSpelling( const wxString& check );
	/// retrieves all predefined language names, used as key to get the filename
	void GetAllLanguageKeyNames( wxArrayString& lang );
	/// checks for predefined language names, which could be found in path
	void GetAvailableLanguageKeyNames( const wxString& path, wxArrayString& lang );
	/// returns the base filename for language key without extension
	wxString GetLanguageShort( const wxString& key ) { return m_languageList[key]; }
	/// sets the dictionary path
	void SetDictionaryPath( const wxString& dicPath ) { m_dicPath = dicPath; }
	/// returns the dictionary path
	const wxString& GetDictionaryPath() const { return m_dicPath; }
	/// sets the dictionary base filename
	void SetDictionary( const wxString& dictionary ) { m_dictionary = dictionary; }
	/// returns the current dictionary base filename
	const wxString& GetDictionary() const { return m_dictionary; }
	///
	void AddWord( const wxString& word ) { Hunspell_add( m_pSpell, word ); }

	void            SetUserDictPath( const wxString& userDictPath ) { this->m_userDictPath = userDictPath; }
	const wxString& GetUserDictPath() const { return m_userDictPath; }

	/// sets plugin pointer
	void SetPlugIn( SpellCheck* plugin ) { m_pPlugIn = plugin; }
	/// enables/disables scanner types
	void EnableScannerType( int type, bool state );
	/// checks if type is set
	bool IsScannerType( int type ) { return ( m_scanners & type ); }

	void AddWordToUserDict( const wxString& word );

	void AddWordToIgnoreList( const wxString& word );

	enum
	{
		// types to scan for GetStyleAtPos
		SCT_C_COM   = 1, // C comments
		SCT_CPP_COM = 2, // CPP comments
		SCT_DOX_1   = 3, // doxygen */
		SCT_STRING  = 6, // strings
		SCT_DOX_2   = 15 // doxygen ///
	};

	enum    // type flags to check
	{
		kString     = 0x01,
		kCppComment = 0x02,
		kCComment   = 0x04,
		kDox1       = 0x08,
		kDox2       = 0x10
	};

	enum    // CheckCppType return values
	{
		kNoSpellingError = 0,
		kSpellingError,
		kSpellingCanceled
	};

protected:
	int  CheckCppType( IEditor* pEditor );
	int  MarkErrors( IEditor* pEditor );
	void InitLanguageList();

	bool     LoadUserDict( const wxString& filename );
	bool     SaveUserDict( const wxString& filename );
	wxString GetCharacterEncoding();

	wxString      m_dicPath;         // dictionary path
	wxString      m_dictionary;      // dictionary base filename
	wxString      m_userDictPath;    // path to save user dictionary
	Hunhandle*    m_pSpell;          // pointer to hunspell
	wxArrayString m_ignoreList;      // ignore list
	wxArrayString m_userDict;        // user words
	languageMap   m_languageList;    // list with predefined language keys
	SpellCheck*   m_pPlugIn;         // pointer to plugin

	CorrectSpellingDlg* m_pSpellDlg; // pointer to correction dialog

	partList m_parseValues;          // list with position results for CPP parsing

	int m_scanners;                  // flags for scanner types
};
#endif // _HUNSPELLINTERFACE_
