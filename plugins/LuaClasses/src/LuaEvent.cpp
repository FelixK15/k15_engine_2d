#include "LuaEvent.h"
#include "EventManager.h"
#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaEvent>::LuaCFunction LuaEvent::m_functions[] = {
	toLuaCFunction(LuaEvent,fire),
	toLuaCFunction(LuaEvent,addToQueue),
	toLuaCFunction(LuaEvent,getArgument),
	toLuaCFunction(LuaEvent,setArgument),
	toLuaCFunction(LuaEvent,getType),
	{0,0}
};

LuaEvent::LuaEvent(const String& eventname)
	: LuaAble(), m_event(eventname.c_str())
{

}

LuaEvent::LuaEvent( const Event& originEvent )
	: LuaAble(), m_event(originEvent)
{

}

int LuaEvent::getArgument(lua_State *state)
{
	if(lua_isstring(state,-1)){
		String argumentName = LUA_GET_STRING(-1);

		Variant argument = m_event.getArgument(argumentName);
		if(argument.type == TYPE_EMPTY){
			LUA_PRINT_ERROR("There's no event argument with the name \"" + argumentName + "\" for the event \"" + m_event.getType().getString() + "\".");
			lua_pushnil(m_state);
		}else{
			LUA_PUSH_VARIANT(m_state,argument);
		}
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"String\".");
		lua_pushnil(state);
	}

	return 1;
}

int LuaEvent::fire(lua_State *state)
{
	EventManager::getInstance()->triggerEvent(m_event);

	return 0;
}

int LuaEvent::addToQueue(lua_State *state)
{
	EventManager::getInstance()->addEventToQueue(m_event);

	return 0;
}

int LuaEvent::getType(lua_State *state)
{
	lua_pushnumber(state,m_event.getType().getIdentifier());

	return 1;
}

int LuaEvent::setArgument(lua_State *state)
{
	if(lua_isstring(state,-2)){
		int typeOfArgument = lua_type(state,-1);

		if(typeOfArgument == LUA_TNUMBER || typeOfArgument == LUA_TSTRING || typeOfArgument == LUA_TBOOLEAN){
			String argumentName = LUA_GET_STRING(-2);
			if(typeOfArgument == LUA_TNUMBER){
				m_event.setArgument(argumentName,Variant(LUA_GET_DOUBLE(-1)));
			}else if(typeOfArgument == LUA_TSTRING){
				m_event.setArgument(argumentName,Variant(LUA_GET_STRING(-1)));
			}else{
				m_event.setArgument(argumentName,Variant(LUA_GET_BOOL(-1)));
			}

			lua_pushboolean(state,TO_C_BOOL(true));
		}else{
			LUA_PRINT_ERROR("1st argument is type \"String\", but 2nd argument is an undefined type.)");
			lua_pop(state,2); //Pop the arguments from the stack.
			lua_pushboolean(state,TO_C_BOOL(false));
		}
	}else{
		LUA_PRINT_ERROR("1st argument needs to be from type \"String\".");
		lua_pop(state,2); //Pop the arguments from the stack.
		lua_pushboolean(state,TO_C_BOOL(false));
	}

	return 1;
}