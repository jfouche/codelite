#ifndef CL_LUA_BINDINGS_H_INCLUDED
#define CL_LUA_BINDINGS_H_INCLUDED

#include "lua_utils.hpp"

class IEditor;
class IManager;
class Project;
class Workspace;
class wxCommandEvent;
class clCommandEvent;

static const char* IMANAGER_CLASSNAME = "IManager";
static const char* IEDITOR_CLASSNAME = "IEditor";
static const char* PROJECT_CLASSNAME = "Project";
static const char* WORKSPACE_CLASSNAME = "Workspace";
static const char* WX_EVT_CLASSNAME = "wxCommandEvent";
static const char* CL_EVT_CLASSNAME = "clCommandEvent";

void lua_open_Codelite(lua_State* L, IManager* manager, const char* name);
void lua_open_IManager(lua_State* L);
void lua_open_IEditor(lua_State* L);
void lua_open_Project(lua_State* L);
void lua_open_Workspace(lua_State* L);
void lua_open_Events(lua_State* L);

#endif // CL_LUA_BINDINGS_H_INCLUDED
