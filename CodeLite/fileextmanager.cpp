#include "fileextmanager.h"
#include <wx/filename.h>

std::map<wxString, FileExtManager::FileType> FileExtManager::m_map;

void FileExtManager::Init()
{
    static bool init_done(false);

    if ( !init_done ) {
        init_done = true;

        m_map[wxT("cc") ] = TypeSourceCpp;
        m_map[wxT("cpp")] = TypeSourceCpp;
        m_map[wxT("cxx")] = TypeSourceCpp;
        m_map[wxT("c++")] = TypeSourceCpp;
        m_map[wxT("c")  ] = TypeSourceC;

        m_map[wxT("h")   ] = TypeHeader;
        m_map[wxT("hpp") ] = TypeHeader;
        m_map[wxT("hxx") ] = TypeHeader;
        m_map[wxT("hh")  ] = TypeHeader;
        m_map[wxT("h++") ] = TypeHeader;
        m_map[wxT("inc") ] = TypeHeader;
        m_map[wxT("incl")] = TypeHeader;
        m_map[wxT("inl") ] = TypeHeader;

        m_map[wxT("rc")  ] = TypeResource;
        m_map[wxT("res") ] = TypeResource;

        m_map[wxT("y")   ] = TypeYacc;
        m_map[wxT("l")   ] = TypeLex;
        m_map[wxT("ui")  ] = TypeQtForm;
        m_map[wxT("qrc") ] = TypeQtResource;

        m_map[wxT("project") ]   = TypeProject;
        m_map[wxT("workspace") ] = TypeWorkspace;
        m_map[wxT("fbp") ] = TypeFormbuilder;
        m_map[wxT("cdp") ] = TypeCodedesigner;
        m_map[wxT("erd") ] = TypeErd;

        m_map[wxT("php")]   = TypePhp;
        m_map[wxT("inc")]   = TypePhp;
        m_map[wxT("phtml")] = TypePhp;

        m_map[wxT("xml")] = TypeXml;
        m_map[wxT("xrc")] = TypeXRC;
        m_map[wxT("css")] = TypeCSS;
        m_map[wxT("js")]  = TypeJS;
        m_map[wxT("py")]  = TypePython;

        m_map[wxT("exe")] = TypeExe;
        m_map[wxT("html")] = TypeHtml;
        m_map[wxT("htm")] = TypeHtml;

        m_map[wxT("tar")]   = TypeArchive;
        m_map[wxT("a")]     = TypeArchive;
        m_map[wxT("lib")]   = TypeArchive;
        m_map[wxT("zip")]   = TypeArchive;
        m_map[wxT("rar")]   = TypeArchive;
        m_map[wxT("targz")] = TypeArchive;

        m_map[wxT("dll")]    = TypeDll;
        m_map[wxT("so")]     = TypeDll;
        m_map[wxT("dylib")]  = TypeDll;

        m_map[wxT("bmp")]  = TypeBmp;
        m_map[wxT("jpeg")] = TypeBmp;
        m_map[wxT("jpg")]  = TypeBmp;
        m_map[wxT("png")]  = TypeBmp;
        m_map[wxT("ico")]  = TypeBmp;
        m_map[wxT("xpm")]  = TypeBmp;

        m_map[wxT("mk")] = TypeMakefile;

        m_map[wxT("log")] = TypeText;
        m_map[wxT("txt")] = TypeText;
        m_map[wxT("ini")] = TypeText;

        m_map[wxT("script")] = TypeScript;
        m_map[wxT("sh")]     = TypeScript;
        m_map[wxT("bat")]    = TypeScript;
        m_map[wxT("bash")]   = TypeScript;

        m_map[wxT("wxcp")] = TypeWxCrafter;
        m_map[wxT("xrc") ] = TypeXRC;

        m_map[wxT("sql")]     = TypeSQL;
        m_map[wxT("phpwsp")]  = TypeWorkspacePHP;
        m_map[wxT("phptags")] = TypeWorkspacePHPTags;
        
        m_map["s"] = TypeAsm;
    }
}

FileExtManager::FileType FileExtManager::GetType(const wxString& filename)
{
    Init();

    wxFileName fn( filename );
    if ( fn.IsOk() == false ) {
        return TypeOther;
    }

    wxString e ( fn.GetExt() );
    e.MakeLower();
    e.Trim().Trim(false);

    std::map<wxString, FileType>::iterator iter = m_map.find(e);
    if ( iter == m_map.end() ) {
        // try to see if the file is a makefile
        if(fn.GetFullName().CmpNoCase(wxT("makefile")) == 0) {
            return TypeMakefile;
        }
        return TypeOther;
    }
    return iter->second;
}
