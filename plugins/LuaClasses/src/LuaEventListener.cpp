#include "LuaEventListener.h"
#include "EventManager.h"
#include "LuaEvent.h"
#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaEventListener>::LuaCFunction LuaEventListener::m_functions[] = {
	toLuaCFunction(LuaEventListener,setEvent),
	toLuaCFunction(LuaEventListener,getEvent),
	{0,0}
};

LuaEventListener::LuaEventListener()
	: LuaAble(), m_event("")
{

}

LuaEventListener::LuaEventListener(const String& eventName)
	: LuaAble(), m_event(eventName.c_str())
{
	ADD_LISTENER(this,m_event.getType());
}

K15_Engine::LuaEventListener::~LuaEventListener()
{
	REMOVE_LISTENER(this,m_event.getType());
}

int LuaEventListener::setEvent( lua_State *state )
{
	if(lua_gettop(m_state) == 0){
		LUA_PRINT_ERROR("The function setEvent expects 1 parameter.");
		lua_pushboolean(m_state,TO_C_BOOL(false));

		return 1;
	}
	if(!lua_istable(m_state,-1)){
		LUA_PRINT_ERROR("Argument for function setEvent has been passed. But it must be from the type \"K15Games.Event\".");
		lua_pushboolean(m_state,TO_C_BOOL(false));
	
		return 1;
	}

	GET_OBJECT_TABLE(m_state);
	GET_OBJECT_VALUE(m_state,"0");
	lua_gettable(m_state,-2);

	if(!lua_islightuserdata(m_state,-1)){
		LUA_PRINT_ERROR("Lua table from type \"EventLitener\" is corrupted. Didn't found the this entry.");
		lua_pushboolean(m_state,TO_C_BOOL(false));

		return 1;
	}else if(!lua_isnil(m_state,-1)){
		LUA_PRINT_ERROR("Lua table from type \"EventLitener\" is corrupted. Found the this entry but it's no userdata.");
		lua_pop(m_state,1);
		REMOVE_OBJECT_TABLE(m_state);

		lua_pushboolean(m_state,TO_C_BOOL(false));
		return 1;
	}
	
	LuaEvent *luaEvent = static_cast<LuaEvent*>(lua_touserdata(state,-1));
	m_event = luaEvent->getEvent();

	REMOVE_OBJECT_TABLE(m_state);
	
	lua_pushboolean(m_state,TO_C_BOOL(true));

	REMOVE_LISTENER(this,m_event.getType());
	ADD_LISTENER(this,m_event.getType());
	return 1;
}

int LuaEventListener::getEvent( lua_State *state )
{
	new LuaEvent(m_event);

	return 1;
}

bool LuaEventListener::handleEvent( const Event& gameEvent )
{
	bool ret = false;

	if(gameEvent.getType() == m_event.getType()){
		GET_OBJECT_TABLE(m_state);

		DO_IF_IS_FUNCTION(m_state,"handleEvent"){
			GET_OBJECT_TABLE(m_state);
			new LuaEvent(gameEvent);
			TRY_TO_CALL_FUNCTION(m_state,2,1);

			if(!lua_isboolean(m_state,-1)){
				LUA_PRINT_ERROR("The function handleEvent of the table from type \"EventListener\" returned not a boolean.!");
			}

			ret = LUA_GET_BOOL(-1);
		}

		REMOVE_OBJECT_TABLE(m_state);
	}

	return ret;
}