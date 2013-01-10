
#include "LuaScript.h"
#include "LuaManager.h"
#include "Game.h"

using namespace K15_Engine;

LuaScript::LuaScript(const String& scriptFile)
	: m_scriptFile(scriptFile)
{
	m_scriptFileLoaded = false;
}

LuaScript::~LuaScript()
{

}

bool LuaScript::execute()
{
	return execute("",NULL);
}

bool LuaScript::execute(const String& functionName)
{
	return execute(functionName,NULL);
}

bool LuaScript::execute( const String& functionName,ArgumentList *arguments )
{
	lua_State *state = LuaManager::getLuaState();
	if(state == NULL){
		WRITE_ERRORLOG("There's no lua state.");
		return false;
	}
	int args = 0;

	if(!m_scriptFileLoaded){
		if(!_loadScriptFile()){
			String error = LUA_GET_STRING(-1);
			WRITE_ERRORLOG("Could not load scriptfile \"" + m_scriptFile + "\" (" + error + ")");
			return false;
		}else{
			WRITE_LOG("Lua scriptfile \"" + m_scriptFile + "\" loaded successful.");
			//function name == empty, lua file itself is the function,
			//so no more functions needs to be called.
			if(!functionName.empty()){
				lua_getfield(state,LUA_REGISTRYINDEX,functionName.c_str());
				//return true;
			}
		}
	}

	if(arguments != NULL){
		args = arguments->size();
		for(ArgumentList::iterator i = arguments->begin();i != arguments->end(); i++){
			Variant_Type type = (*i).type;
			Variant variant = (*i);
			if(type == TYPE_BOOL){
				lua_pushboolean(state,variant.toBool ? 1 : 0);
			}else if(type == TYPE_INTEGER){
				lua_pushinteger(state,variant.toInteger);
			}else if(type == TYPE_STRING){
				lua_pushstring(state,variant.toString);
			}else if(type == TYPE_FLOAT){
				lua_pushinteger(state,(int)variant.toFloat);
			}
		}
	}

	int result = lua_pcall(state,args,0,0);
	
	if(result != 0){
		WRITE_LUA(LUA_GET_STRING(-1));
		return false;
	}

	if(lua_isboolean(state,-1)){
		m_returnVal = Variant(LUA_GET_BOOL(-1));
	}else if(lua_isnumber(state,-1)){
		m_returnVal = Variant(LUA_GET_INTEGER(-1));
	}else if(lua_isstring(state,-1)){
		String string = LUA_GET_STRING(-1);
		m_returnVal = Variant(string);
	}

	return true;
}

ReturnValue LuaScript::getReturnValue()
{
	return m_returnVal;
}

bool LuaScript::_loadScriptFile()
{
	lua_State *state = LuaManager::getLuaState();

	String file = m_scriptFile;
	std::vector<String> directories = myGame->getSystemManager()->getFilesFromDirectory("scripts");
	std::vector<String>::iterator currentDirectory = directories.begin() + 2;

	//The system tries to load the script from the games root directory, the "script" directory and any subdirectory of the "script" directory.
	do{
		int result = luaL_loadfile(state,file.c_str());
		m_scriptFileLoaded = result == 0;
		
		if(!m_scriptFileLoaded){
			if(result != LUA_ERRFILE){
				WRITE_ERRORLOG("Couldn't open Lua file \""+file+"\"(" + LUA_GET_ERROR() + ".");
			}else{
				//pop the error message of the "file not found" error from the stack.
				lua_pop(state,1);
			}
		}
		if(currentDirectory != directories.end()){
			file = (*currentDirectory++) + "\\" + m_scriptFile;
		}else{
			break;
		}
	}while (!m_scriptFileLoaded);
	
	return m_scriptFileLoaded;
}
