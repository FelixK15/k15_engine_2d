#include "LuaObject.h"
#include "LuaManager.h"
#include "LuaScript.h"

using namespace K15_Engine;

int LuaObject::countReferences()
{
	int references = 0;
	lua_State *state = LuaManager::getLuaState();

	luaL_dofile(state,"C:\\Users\\Felix Klinge\\Documents\\Projects\\C++\\K15 Engine\\engine test\\bin\\Debug\\scripts\\startup\\luatraverse.lua");
	lua_getglobal(state,"countreferences");

	if(lua_isfunction(state,-1)){
		lua_rawgeti(state,LUA_REGISTRYINDEX,m_reference);
		if(lua_istable(state,-1)){
			if(lua_pcall(state,1,1,0) != 0){
				LUA_PRINT_ERROR(LUA_GET_STRING(-1));
			}else{
				references = LUA_GET_INTEGER(-1);
			}
		}else if(!lua_isnoneornil(state,-1)){
			lua_remove(state,-1);
		}
	}else if(!lua_isnoneornil(state,-1)){
		lua_remove(state,-1);
	}


	return references;
}