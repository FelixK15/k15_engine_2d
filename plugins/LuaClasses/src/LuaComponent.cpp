#include "LuaComponent.h"
#include "LuaGameObject.h"
#include "LuaEvent.h"

#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaComponent>::LuaCFunction LuaComponent::m_functions[] = {
	toLuaCFunction(LuaComponent,getParent),
	END_LUA_C_FUNCTION()
};

LuaComponent::LuaComponent(const String& type)
	: AbstractComponent(type), LuaAble()
{

}

int K15_Engine::LuaComponent::getParent( lua_State *state )
{
	GameObject* gameobject = AbstractComponent::getParent();
	if(gameobject != NULL){
		new LuaGameObject(*gameobject);
	}else{
		lua_pushnil(m_state);
		LUA_PRINT_ERROR("Component \"" + m_type + "\" has not been assigned to a GameObject yet.");
	}

	return 1;
}

void LuaComponent::setDebugMode( bool val )
{
	GET_OBJECT_TABLE(m_state);
	GET_OBJECT_VALUE(m_state,"setDebugMode");

	if(!lua_isfunction(m_state,-1)){
		GET_OBJECT_TABLE(m_state);
		lua_pushboolean(m_state,TO_C_BOOL(val));
		TRY_TO_CALL_FUNCTION(m_state,2,0);
	}
	REMOVE_OBJECT_TABLE(m_state);
}

AbstractComponent * LuaComponent::clone()
{
	//ToDo

	return NULL;
}

bool LuaComponent::handleMessage( const Event &gameEvent )
{
	bool ret = false;

	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"handleMessage"){
		GET_OBJECT_TABLE(m_state);
		new LuaEvent(gameEvent);
		TRY_TO_CALL_FUNCTION(m_state,2,1);

		if(lua_gettop(m_state) > 1){
			if(lua_isboolean(m_state,-1)){
				ret = TO_CPP_BOOL(lua_toboolean(m_state,-1));
			}else{
				//pop whatever is on the stack.
				lua_pop(m_state,1);
				LUA_PRINT_ERROR("function handleMessage of the component \"" + m_type + "\" did not return a boolean.");
			}
		}else{
			LUA_PRINT_ERROR("function handleMessage of the component \"" + m_type + "\" returned nothing.");
		}
	}
	
	REMOVE_OBJECT_TABLE(m_state);

	return ret;
}

void LuaComponent::start()
{
	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"start"){
		GET_OBJECT_TABLE(m_state);
		TRY_TO_CALL_FUNCTION(m_state,1,0);
	}

	REMOVE_OBJECT_TABLE(m_state);
}

void LuaComponent::setSize( const Size& size )
{
	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"setSize"){
		GET_OBJECT_TABLE(m_state);
		LUA_PUSH_SIZE(m_state,size.getWidth(),size.getHeight());
		TRY_TO_CALL_FUNCTION(m_state,2,0);
	}

	REMOVE_OBJECT_TABLE(m_state);
}

void LuaComponent::setPosition( const Position& position )
{
	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"setPosition"){
		GET_OBJECT_TABLE(m_state);
		LUA_PUSH_POSITION(m_state,position.getX(),position.getY());
		TRY_TO_CALL_FUNCTION(m_state,2,0);
	}

	REMOVE_OBJECT_TABLE(m_state);
}

void LuaComponent::setAngle( S16 angle )
{
	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"setAngle"){
		GET_OBJECT_TABLE(m_state);
		lua_pushnumber(m_state,angle);
		TRY_TO_CALL_FUNCTION(m_state,2,0);
	}

	REMOVE_OBJECT_TABLE(m_state);
}

void LuaComponent::shutdown()
{
	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"shutdown"){
		GET_OBJECT_TABLE(m_state);
		TRY_TO_CALL_FUNCTION(m_state,1,0);
	}

	REMOVE_OBJECT_TABLE(m_state);
}
void LuaComponent::update( U32 gameTime )
{
	GET_OBJECT_TABLE(m_state);

	DO_IF_IS_FUNCTION(m_state,"update"){
		GET_OBJECT_TABLE(m_state);
		lua_pushnumber(m_state,gameTime);
		TRY_TO_CALL_FUNCTION(m_state,2,0);
	}

	REMOVE_OBJECT_TABLE(m_state);
}