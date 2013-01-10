#include "LuaState.h"
#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaState>::LuaCFunction LuaState::m_functions[] = {
	{0,0}
};

LuaState::LuaState()
	: LuaAble()
{

}

bool LuaState::start()
{
	//Push table to the stack
	GET_OBJECT_TABLE(m_state);

	//Tell lua what you wanna get.
	lua_pushstring(m_state,"start");

	//Try to get it.
	lua_gettable(m_state,-2);

	GET_OBJECT_TABLE(m_state);

	//Try to call the function.
	TRY_TO_CALL_FUNCTION(m_state,1,1);

	bool ret = false;

	if(lua_isboolean(m_state,-1)){
		ret = TO_CPP_BOOL(LUA_GET_BOOL(-1));
	}else{
		LUA_PRINT_ERROR("Function \"start\" must return a boolean.");
	}

	REMOVE_OBJECT_TABLE(m_state);

	return ret;
}

void LuaState::update(U32 deltaTime)
{
	//Push table to the stack
	GET_OBJECT_TABLE(m_state);

	//Tell lua what you wanna get.
	lua_pushstring(m_state,"update");

	//Try to get it.
	lua_gettable(m_state,-2);

	GET_OBJECT_TABLE(m_state);
	
	//Push argument on the stack.
	lua_pushinteger(m_state,deltaTime);


	//Try to call the function.
	TRY_TO_CALL_FUNCTION(m_state,2,0);

	REMOVE_OBJECT_TABLE(m_state);
}

void LuaState::end()
{
	//Push table to the stack
	GET_OBJECT_TABLE(m_state);

	//Tell lua what you wanna get.
	lua_pushstring(m_state,"update");

	//Try to get it.
	lua_gettable(m_state,-2);

	GET_OBJECT_TABLE(m_state);

	//Try to call the function.
	TRY_TO_CALL_FUNCTION(m_state,1,0);

	REMOVE_OBJECT_TABLE(m_state);
}