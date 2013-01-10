#include "LuaGameWorld.h"
#include "LuaGameObject.h"
#include "LuaGameWorldLayer.h"
#include "Makros.h"

#include "StringConverter.h"

using namespace K15_Engine;

LuaAble<LuaGameWorld>::LuaCFunction LuaGameWorld::m_functions[] = {
	toLuaCFunction(LuaGameWorld,getName),
	toLuaCFunction(LuaGameWorld,addLayer),
	toLuaCFunction(LuaGameWorld,removeLayer),
	toLuaCFunction(LuaGameWorld,addGameObject),
	END_LUA_C_FUNCTION()
};

LuaGameWorld::LuaGameWorld()
	: LuaAble()
{

}

LuaGameWorld::LuaGameWorld(const String& resource)
	: LuaAble()
{
	//ToDo
}

LuaGameWorld::LuaGameWorld(GameWorld& originGameWorld)
{
	m_gameWorld = originGameWorld;
}

int LuaGameWorld::getName( lua_State *state )
{
	lua_pushstring(state,m_gameWorld.getName().c_str());
	return 1;
}

int LuaGameWorld::addLayer( lua_State *state )
{
	if(lua_islightuserdata(state,-1)){ //or lua_istable(state,-1)
		LuaGameWorldLayer *luaLayer = static_cast<LuaGameWorldLayer*>(lua_touserdata(state,-1));
		GameWorldLayer layer = luaLayer->getGameWorldLayer();

		int newIndex = m_gameWorld.addLayer(layer);

		lua_pushnumber(state,newIndex);
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"K15Games.GameWorldLayer\"");
		lua_pushnumber(state,0);
	}

	return 1;
}

int LuaGameWorld::removeLayer( lua_State *state )
{
	if(lua_isnumber(state,-1) || lua_isstring(state,-1)){
		bool result = false;

		if(lua_isnumber(state,-1)){
			int layerIndex = LUA_GET_INTEGER(-1);

			result = m_gameWorld.removeLayer(layerIndex);
		}else{
			String layerName = LUA_GET_STRING(-1);

			result = m_gameWorld.removeLayer(layerName);
		}

		lua_pushboolean(state,TO_C_BOOL(result));
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"string\" or \"integer\".");
		lua_pushboolean(state,FALSE);
	}

	return 1;
}

int LuaGameWorld::addGameObject( lua_State *state )
{
	//Check if the right arguments where passed.
	if(lua_islightuserdata(state,-2) && (lua_isnumber(state,-1) || lua_isstring(state,-1))){
		
		GameWorldLayer *layer = NULL;
		LuaGameObject *luaGameObject = static_cast<LuaGameObject*>(lua_touserdata(state,-2));
		GameObject *gameObject = luaGameObject->getGameObject();

		//do this if integer has been passed as second argument
		if(lua_isnumber(state,-1)){
			int layerID = LUA_GET_INTEGER(-1);

			if(m_gameWorld.getLayerCount() < layerID){
				layer = m_gameWorld.getLayer(layerID);
			}else{
				LUA_PRINT_ERROR("Argument layerID \"" + StringConverter::toString(layerID) + "\" is higher than the amount of layers in the GameWorld (size: \"" + StringConverter::toString(m_gameWorld.getLayerCount()) + "\")");
				lua_pushboolean(state,FALSE);
			}
		}else{
		//do this if string has been passed as second argument
			String layerName = LUA_GET_STRING(-1);

			layer = m_gameWorld.getLayer(layerName);
		}
		
		//check whether layerptr is NULL or not.
		if(layer == NULL){
			LUA_PRINT_ERROR("Gameworld \"" + m_gameWorld.getName() + "\" | layer wasn't found.");
			lua_pushboolean(state,FALSE);
		}else{
			layer->addGameObject(*gameObject);
			lua_pushboolean(state,TRUE);
		}
	}else{
		LUA_PRINT_ERROR("Expected 1st argument \"GameObject\" and 2nd argument \"integer\" or \"string\"");
		lua_pushboolean(state,FALSE);
	}

	return 1;
}
