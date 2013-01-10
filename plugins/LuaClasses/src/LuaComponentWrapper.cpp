#include "LuaComponentWrapper.h"
#include "AbstractComponent.h"
#include "LuaGameObject.h"
#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaComponentWrapper>::LuaCFunction LuaComponentWrapper::m_functions[] = {
	toLuaCFunction(LuaComponentWrapper,getParent),
	END_LUA_C_FUNCTION()
};

LuaComponentWrapper::LuaComponentWrapper(AbstractComponent *component)
	: LuaAble()
{
	m_component = component;
}

LuaComponentWrapper::~LuaComponentWrapper()
{
	SAFE_DELETE(m_component);
}

int K15_Engine::LuaComponentWrapper::getParent( lua_State *state )
{
	if(m_component != NULL){
		GameObject *object = m_component->getParent();
		if(object != NULL){
			new LuaGameObject(*object);

			return 1;
		}
	}

	lua_pushnil(state);

	return 1;
}

AbstractComponent *LuaComponentWrapper::getComponent()
{
	return m_component;
}