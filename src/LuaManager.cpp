#include "LuaManager.h"
#include "Log.h"

using namespace K15_Engine;

lua_State* LuaManager::m_state = NULL;
//LuaObjectList LuaManager::m_objectList;

bool LuaManager::initialize()
{
	bool ret = false;
	if(m_state == NULL){
		m_state = luaL_newstate();

		//Open standard libraries. (i\o,math,etc.)
		luaL_openlibs(m_state);

		if(m_state == NULL){
			WRITE_CRITICALLOG("Lua could not get opened.");
		}else{
			WRITE_DEBUG("LuaManager has been initialized.");
			ret = true;
		}
	}else{
		WRITE_ERRORLOG("LuaManager has already been initialized.");
	}

	return ret;
}

bool LuaManager::shutdown()
{
	bool ret = false;
	if(m_state != NULL){
		lua_close(m_state);
		m_state = NULL;
		WRITE_DEBUG("LuaManager has been shutdown successfully.");
		ret = true;
	}else{
		WRITE_ERRORLOG("LuaManager was not initialized. (call LuaManager::initialize() in order to be able to call LuaManager::shutdown())");
	}

	return ret;
}

lua_State * LuaManager::getLuaState()
{
	return m_state;
}

void LuaManager::printError( const std::string& errormsg )
{
	WRITE_LUA(errormsg);
	luaL_error(m_state,errormsg.c_str());
}

std::string LuaManager::getLuaError()
{
	std::string errormsg = "";
	//Is there something on the stack?
	if(lua_gettop(m_state) > 0){
		//Is a string on top of the stack (the error message)?
		if(lua_isstring(m_state,-1)){
			errormsg = LUA_GET_STRING(-1);
		}
	}

	return errormsg;
}

void LuaManager::update()
{
// 	lua_gc(m_state,LUA_GCRESTART,5);
// 	lua_gc(m_state,LUA_GCCOLLECT,5);

// 	for(LuaObjectList::iterator i = m_objectList.begin();i != m_objectList.end();i++){
// 		LuaObject *object = (*i);
// 
// 		if(object->isDead()){
// 			int ref = object->countReferences();
// 
// 			if(ref == 1){
// 				delete object;
// 				m_objectList.remove(object);
// 			}
// 		}
// 	}
}