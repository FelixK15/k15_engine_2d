#include "LuaGameObject.h"
#include "LuaManager.h"
#include "LuaEvent.h"
#include "LuaComponentWrapper.h"
#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaGameObject>::LuaCFunction LuaGameObject::m_functions[] =	{toLuaCFunction(LuaGameObject,getID),
																	 toLuaCFunction(LuaGameObject,getType),
																	 toLuaCFunction(LuaGameObject,setType),
																	 toLuaCFunction(LuaGameObject,setNextState),
																	 toLuaCFunction(LuaGameObject,setPosition),
																	 toLuaCFunction(LuaGameObject,setPositionNextTick),
																	 toLuaCFunction(LuaGameObject,setSize),
																	 toLuaCFunction(LuaGameObject,setSizeNextTick),
																	 toLuaCFunction(LuaGameObject,setAngle),
																	 toLuaCFunction(LuaGameObject,setAngleNextTick),
																	 toLuaCFunction(LuaGameObject,autoUpdate),
																	 toLuaCFunction(LuaGameObject,getAngle),
																	 toLuaCFunction(LuaGameObject,getSize),
																	 toLuaCFunction(LuaGameObject,getPosition),
																	 toLuaCFunction(LuaGameObject,restorePosition),
																	 toLuaCFunction(LuaGameObject,restoreSize),
																	 toLuaCFunction(LuaGameObject,restoreAngle),
																	 toLuaCFunction(LuaGameObject,addComponent),
																	 toLuaCFunction(LuaGameObject,removeComponent),
																	 toLuaCFunction(LuaGameObject,broadcastMessage),
																	 toLuaCFunction(LuaGameObject,update),
																	 toLuaCFunction(LuaGameObject,setDebugMode),
																	 END_LUA_C_FUNCTION()};



#define GET_1_INTEGER_AND_PERFORM_FUNCTION(func) int i1 = LUA_GET_INTEGER(-2); \
													m_gameObject.func(i1);

#define GET_2_INTEGER_AND_PERFORM_FUNCTION(func) int i1 = LUA_GET_INTEGER(-2); \
												 int i2 = LUA_GET_INTEGER(-1); \
											     m_gameObject.func(i1,i2);

LuaGameObject::LuaGameObject()
	: LuaAble()
{

}

LuaGameObject::LuaGameObject(const String &type)
	: LuaAble()
{
	m_gameObject.setType(type);
}

LuaGameObject::LuaGameObject(const GameObject &gameobject)
	: LuaAble()
{
	m_gameObject = gameobject;
}

LuaGameObject::~LuaGameObject()
{

}

int LuaGameObject::getID(lua_State *state)
{
	lua_pushinteger(state,m_gameObject.getID());
	return 1;
}

int LuaGameObject::getType(lua_State *state)
{
	lua_pushstring(state,m_gameObject.getType().c_str());
	return 1;
}

int LuaGameObject::setType(lua_State *state)
{
	if(lua_isstring(state,-1)){
		String type = LUA_GET_STRING(-1);
		m_gameObject.setType(type);
	}

	return 0;
}

int LuaGameObject::setNextState(lua_State *state)
{
	return 0;
}

int LuaGameObject::setPosition(lua_State *state)
{
	GET_2_INTEGER_AND_PERFORM_FUNCTION(setPosition);

	return 0;
}

int LuaGameObject::setPositionNextTick(lua_State *state)
{
	GET_2_INTEGER_AND_PERFORM_FUNCTION(setPositionNextTick);

	return 0;
}

int LuaGameObject::setSize(lua_State *state)
{
	GET_2_INTEGER_AND_PERFORM_FUNCTION(setSize);

	return 0;
}

int LuaGameObject::setSizeNextTick(lua_State *state)
{
	GET_2_INTEGER_AND_PERFORM_FUNCTION(setSizeNextTick);

	return 0;
}

int LuaGameObject::setAngle(lua_State *state)
{
	GET_1_INTEGER_AND_PERFORM_FUNCTION(setAngle);

	return 0;
}

int LuaGameObject::setAngleNextTick(lua_State *state)
{
	GET_1_INTEGER_AND_PERFORM_FUNCTION(setAngleNextTick);

	return 0;
}

int LuaGameObject::autoUpdate(lua_State *state)
{
	if(TO_CPP_BOOL(lua_isboolean(state,-1))){
		bool b = TO_CPP_BOOL(lua_isboolean(state,-1));
		m_gameObject.autoUpdate(b);
	}

	return 0;
}

int LuaGameObject::getAngle(lua_State *state)
{
	lua_pushinteger(state,m_gameObject.getAngle());

	return 1;
}

int LuaGameObject::getPosition(lua_State *state)
{
	LUA_PUSH_POSITION(state,m_gameObject.getPosition().getX(),m_gameObject.getPosition().getY());

	return 1;
}

int LuaGameObject::getSize(lua_State *state)
{
	LUA_PUSH_SIZE(state,m_gameObject.getSize().getWidth(),m_gameObject.getSize().getHeight());

	return 1;
}

int LuaGameObject::restorePosition(lua_State *state)
{
	m_gameObject.restorePosition();

	return 0;
}

int LuaGameObject::restoreSize(lua_State *state)
{
	m_gameObject.restoreSize();

	return 0;
}

int LuaGameObject::restoreAngle(lua_State *state)
{
	m_gameObject.restoreAngle();

	return 0;
}

int LuaGameObject::addComponent(lua_State *state)
{
	if(!lua_istable(state,-1)){
		LUA_PRINT_ERROR("Expected argument of type \"K15Engine.Component\".");
		lua_pushboolean(state,TO_C_BOOL(false));
		return 1;
	}
	//Get the "this pointer" of the table on the stack (the component)
	TRY_TO_GET_THIS_POINTER(state,-2);

	if(!lua_isuserdata(state,-1)){
		LUA_PRINT_ERROR("Component is corrupted or is not from type \"K15Engine.Component\" this-ptr is null.");
		lua_pushboolean(state,TO_C_BOOL(false));
		return 1;
	}

	LuaComponentWrapper *wrapper = static_cast<LuaComponentWrapper*>(LUA_GET_USERDATA(-1));

	if(wrapper != NULL){
		AbstractComponent *component = wrapper->getComponent();
		lua_pushboolean(state,TO_C_BOOL(m_gameObject.addComponent(component)));
	}else{
		lua_pushboolean(state,TO_C_BOOL(false));
	}

	return 1;
}

int LuaGameObject::removeComponent(lua_State *state)
{
	if(!lua_isstring(state,-1)){
		LUA_PRINT_ERROR("Expected argument of type \"string\".");
		lua_pushboolean(state,TO_C_BOOL(false));
		return 1;
	}

	String type = LUA_GET_STRING(-1);
	lua_pushboolean(state,TO_C_BOOL(m_gameObject.removeComponent(type)));

	return 1;
}

int LuaGameObject::broadcastMessage(lua_State *state)
{
	if(!lua_istable(state,-1)){
		LUA_PRINT_ERROR("Expected argument of type \"K15Engine.Event\".");
		return 0;
	}

	TRY_TO_GET_THIS_POINTER(state,-2);

	if(!lua_isuserdata(state,-1)){
		LUA_PRINT_ERROR("Component is corrupted or is not from type \"K15Engine.Component\" this-ptr is null.");
	}else{
		LuaEvent *luaEvent = static_cast<LuaEvent*>(LUA_GET_USERDATA(-1));
		if(luaEvent != NULL){
			m_gameObject.broadcastMessage(luaEvent->getEvent());
		}
	}

	return 0;
}

int LuaGameObject::update(lua_State *state)
{
	if(lua_isnumber(state,-1)){
		int deltatime = LUA_GET_INTEGER(-1);
		m_gameObject.update(deltatime);
	}

	return 0;
}

int LuaGameObject::setDebugMode(lua_State *state)
{
	if(TO_CPP_BOOL(lua_isboolean(state,-1))){
		m_gameObject.setDebugMode(TO_CPP_BOOL(LUA_GET_BOOL(-1)));
	}

	return 0;
}