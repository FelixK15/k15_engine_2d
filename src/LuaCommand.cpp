#include "LuaCommand.h"

#include "LuaManager.h"
#include "Log.h"
using namespace K15_Engine;

LuaCommand::LuaCommand(const String& command)
	: m_command(command),
	  m_errorMessage(""),
	  m_executedSuccessful(false)
{
	
}

bool LuaCommand::execute()
{
	lua_State *state = LuaManager::getLuaState();

	if(state == NULL){
		m_executedSuccessful = false;
		m_errorMessage = "LuaManager::getLuaState() returned NULL.";
	}else{
		m_executedSuccessful = (luaL_loadbuffer(state,m_command.c_str(),m_command.size(),"LuaCommand") == 0);
		if(!executedSuccessful()){
			m_errorMessage = lua_tostring(state,-1);
		}
	}

	return executedSuccessful();
}
