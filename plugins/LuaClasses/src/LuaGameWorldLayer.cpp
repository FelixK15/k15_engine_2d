#include "LuaGameWorldLayer.h"
#include "LuaGameObject.h"

#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaGameWorldLayer>::LuaCFunction LuaGameWorldLayer::m_functions[] = {
	toLuaCFunction(LuaGameWorldLayer,getName),
	toLuaCFunction(LuaGameWorldLayer,setName),
	toLuaCFunction(LuaGameWorldLayer,isCollisionLayer),
	toLuaCFunction(LuaGameWorldLayer,setAsCollisionLayer),
	toLuaCFunction(LuaGameWorldLayer,getScrollSpeed),
	toLuaCFunction(LuaGameWorldLayer,setScrollSpeed),
	toLuaCFunction(LuaGameWorldLayer,addGameObject),
	END_LUA_C_FUNCTION()
};

LuaGameWorldLayer::LuaGameWorldLayer()
{

}

LuaGameWorldLayer::LuaGameWorldLayer(const String& name)
{
	m_layer.setName(name);
}

LuaGameWorldLayer::LuaGameWorldLayer(GameWorldLayer& originLayer)
{
	m_layer = originLayer;
}

int LuaGameWorldLayer::getName( lua_State *state )
{
	lua_pushstring(state,m_layer.getName().c_str());

	return 1;
}

int LuaGameWorldLayer::setName( lua_State *state )
{
	if(lua_isstring(state,-1)){
		String layerName = LUA_GET_STRING(-1);

		m_layer.setName(layerName);
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"string\".");
	}

	return 0;
}

int LuaGameWorldLayer::isCollisionLayer( lua_State *state )
{
	lua_pushboolean(state,m_layer.isCollisionLayer());

	return 1;
}

int LuaGameWorldLayer::setAsCollisionLayer( lua_State *state )
{
	if(lua_isboolean(state,-1)){
		bool collLayer = LUA_GET_BOOL(-1);
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"boolean\".");
	}

	return 0;
}

int LuaGameWorldLayer::getScrollSpeed( lua_State *state )
{
	lua_pushnumber(state,m_layer.getScrollSpeed());

	return 1;
}

int LuaGameWorldLayer::setScrollSpeed( lua_State *state )
{
	bool ret = false;

	if(lua_isnumber(state,-1)){
		float newScrollSpeed = (float)lua_tonumber(state,-1);

		m_layer.setScrollSpeed(newScrollSpeed);
		ret = true;
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"number\".");
	}

	lua_pushboolean(state,TO_C_BOOL(ret));
	return 1;
}

int LuaGameWorldLayer::addGameObject( lua_State *state )
{
	bool ret = false;

	if(lua_istable(state,-1)){
		lua_pushnumber(state,0);
		lua_gettable(state,-2);

		if(lua_islightuserdata(state,-1)){
			LuaGameObject *object = static_cast<LuaGameObject*>(LUA_GET_USERDATA(-1));
			GameObject *gameobject = object->getGameObject();

			m_layer.addGameObject(*gameobject);
			ret = true;
		}

		lua_pop(state,2); // pop whatever was at the tables 0. index from the stack.
	}

	if(!ret){
		LUA_PRINT_ERROR("Argument of type \"K15Engine.GameObject\" expected.");
	}

	lua_pushboolean(state,TO_C_BOOL(ret));

	return 1;
}
