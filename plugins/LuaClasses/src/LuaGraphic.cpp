#include "LuaGraphic.h"
#include "Game.h"
#include "IGraphic.h"
#include "Makros.h"

using namespace K15_Engine;

LuaAble<LuaGraphic>::LuaCFunction LuaGraphic::m_functions[] =	{toLuaCFunction(LuaGraphic,setColorkey),
																	toLuaCFunction(LuaGraphic,rotate),
																	toLuaCFunction(LuaGraphic,isLocked),
																	toLuaCFunction(LuaGraphic,getAlpha),
																	toLuaCFunction(LuaGraphic,setPosition),
																	toLuaCFunction(LuaGraphic,setSize),
																	toLuaCFunction(LuaGraphic,setVisible),
																	toLuaCFunction(LuaGraphic,attachToScreen),
																	toLuaCFunction(LuaGraphic,detachFromScreen),
																	toLuaCFunction(LuaGraphic,isScreenAttached),
																	toLuaCFunction(LuaGraphic,isVisible),
																	toLuaCFunction(LuaGraphic,getSize),
																	toLuaCFunction(LuaGraphic,setPixel),
																	toLuaCFunction(LuaGraphic,fillWithColor),
																	toLuaCFunction(LuaGraphic,getPixel),
																	toLuaCFunction(LuaGraphic,cutRect),
																	toLuaCFunction(LuaGraphic,setDrawOutOfBounds),
																	toLuaCFunction(LuaGraphic,drawOutOfBounds),
																	toLuaCFunction(LuaGraphic,drawOutOfBounds),
																	toLuaCFunction(LuaGraphic,draw),
																{0,0}};

int loadGraphic(GraphicPtr &graphic,const String& graphicName);

LuaGraphic::LuaGraphic()
{
	m_graphic = myGame->getGraphicManager()->createGraphic();
}

LuaGraphic::LuaGraphic(GraphicPtr originGraphic)
{
	m_graphic = myGame->getGraphicManager()->createGraphic();
	m_graphic->copyFrom(static_cast<IResourceable*>(originGraphic.get()));
}

LuaGraphic::LuaGraphic(const String& resource)
{
	loadGraphic(m_graphic,resource);
}

int LuaGraphic::rotate(lua_State *state)
{
	if(lua_isnumber(state,-1)){
		int angle = LUA_GET_INTEGER(-1);
		m_graphic->rotate(angle);
	}

	return 0;
}

int LuaGraphic::load( lua_State *state )
{
	if(lua_isstring(state,-1)){
		String graphicName = LUA_GET_STRING(-1);
		lua_pushboolean(state,loadGraphic(m_graphic,graphicName));
	}else{
		LuaManager::printError("Expected string argument.");
		lua_pushboolean(state,FALSE);
	}

	return 1;
}

int LuaGraphic::setColorkey(lua_State *state)
{
	if(lua_isnumber(state,-3) && lua_isnumber(state,-2) && lua_isnumber(state,-1)){
		int b = LUA_GET_INTEGER(1);
		int g = LUA_GET_INTEGER(1);
		int r = LUA_GET_INTEGER(1);

		m_graphic->setColorkey(r,g,b);
	}

	return 0;
}

int LuaGraphic::isLocked(lua_State *state)
{
	lua_pushboolean(state,m_graphic->isLocked() == true ? 1 : 0);
	
	return 1;
}

int LuaGraphic::getAlpha(lua_State *state)
{
	lua_pushinteger(state,m_graphic->getAlpha());

	return 1;
}

int LuaGraphic::setPosition(lua_State *state)
{
	if(lua_isnumber(state,-2) && lua_isnumber(state,-1)){
		int y = LUA_GET_INTEGER(1);
		int x = LUA_GET_INTEGER(1);

		m_graphic->setPosition(x,y);
	}

	return 0;
}

int LuaGraphic::setSize(lua_State *state)
{
	if(lua_isnumber(state,-2) && lua_isnumber(state,-1)){
		int h = LUA_GET_INTEGER(1);
		int w = LUA_GET_INTEGER(1);

		m_graphic->setSize(w,h);
	}

	return 0;
}

int LuaGraphic::setVisible(lua_State *state)
{
	if(lua_isboolean(state,-1)){
		bool b = LUA_GET_BOOL(-1);
		m_graphic->setVisible(b);
	}

	return 0;
}

int LuaGraphic::attachToScreen(lua_State *state)
{
	m_graphic->attachToScreen();

	return 0;
}

int LuaGraphic::detachFromScreen(lua_State *state)
{
	m_graphic->detachFromScreen();

	return 0;
}

int LuaGraphic::isScreenAttached(lua_State *state)
{
	lua_pushboolean(state,m_graphic->isScreenAttached() ? 1 : 0);

	return 1;
}

int LuaGraphic::isVisible(lua_State *state)
{
	lua_pushboolean(state,m_graphic->isVisible() ? 1 : 0);

	return 1;
}

int LuaGraphic::getSize(lua_State *state)
{
	LUA_PUSH_SIZE(state,m_graphic->getSize().getHeight(),m_graphic->getSize().getWidth());

	return 1;
}

int LuaGraphic::getPosition(lua_State *state)
{
	LUA_PUSH_POSITION(state,m_graphic->getPosition().getX(),m_graphic->getPosition().getY());

	return 1;
}

int LuaGraphic::setPixel(lua_State *state)
{
	bool hasAlpha = true;

	if(!lua_isnumber(state,-6)){
		hasAlpha = false;
	}
	
	int x = LUA_GET_INTEGER(-1);
	int y = LUA_GET_INTEGER(-2);

	int r = LUA_GET_INTEGER(-3);
	int g = LUA_GET_INTEGER(-4);
	int b = LUA_GET_INTEGER(-5);
	int a = hasAlpha ?  LUA_GET_INTEGER(-6) : 0;

	m_graphic->setPixel(x,y,r,g,b,a);
	//ToDo change to correct lua stack order

	return 0;

}

int LuaGraphic::fillWithColor(lua_State *state)
{
	if(lua_isnumber(state,-4) && lua_isnumber(state,-3) && lua_isnumber(state,-2) && lua_isnumber(state,-1)){
		int a = LUA_GET_INTEGER(1);
		int b = LUA_GET_INTEGER(1);
		int g = LUA_GET_INTEGER(1);
		int r = LUA_GET_INTEGER(1);

		m_graphic->fillWithColor(r,g,b,a);
	}

	return 0;
}

int LuaGraphic::getPixel(lua_State *state)
{
	if(lua_isnumber(state,-1) && lua_isnumber(state,-2)){
		int x = LUA_GET_INTEGER(-1);
		int y = LUA_GET_INTEGER(-2);

		Pixel pixel = m_graphic->getPixel(x,y);
		LUA_PUSH_COLOR(state,pixel.getR(),pixel.getG(),pixel.getB(),pixel.getA());

		return 1;
	}

	return 0;
}

int LuaGraphic::cutRect(lua_State *state)
{
	if(lua_isnumber(state,-4) && lua_isnumber(state,-3) && lua_isnumber(state,-2) && lua_isnumber(state,-1)){
		int x = lua_isnumber(state,-4);
		int y = lua_isnumber(state,-3);
		int w = lua_isnumber(state,-2);
		int h = lua_isnumber(state,-1);

		GraphicPtr newGraphic = m_graphic->cutRect(x,y,w,h);
		new LuaGraphic(newGraphic);

		return 1;
	}

	return 0;
}

int LuaGraphic::setDrawOutOfBounds(lua_State *state)
{
	if(lua_isboolean(state,-1)){
		bool b =LUA_GET_BOOL(-1) == 0 ? false : true;
		m_graphic->setDrawOutOfBounds(b);
	}

	return 0;
}

int LuaGraphic::drawOutOfBounds(lua_State *state)
{
	lua_pushboolean(state,m_graphic->drawOutOfBounds() ? 1 : 0);

	return 1;
}

int LuaGraphic::draw( lua_State *state )
{
	DRAW_GRAPHIC(m_graphic);

	return 0;
}

int loadGraphic(GraphicPtr &graphic,const String& graphicName)
{
	graphic = myGame->getGraphicManager()->createGraphic(graphicName);

	if(graphic->loadedSuccessful()){
		return TRUE;
	}else{
		return FALSE;
	}
}