#include "LuaFont.h"
#include "Game.h"
#include "IFont.h"

using namespace K15_Engine;

LuaAble<LuaFont>::LuaCFunction LuaFont::m_functions[] = {
	toLuaCFunction(LuaFont,load),
	toLuaCFunction(LuaFont,getSize),
	toLuaCFunction(LuaFont,setSize),
	{0,0}
};

int loadFont(FontPtr font,const String& fontName);

LuaFont::LuaFont()
{
	m_font = myGame->getFontManager()->createFont();
}

LuaFont::LuaFont(const String& fontName)
{
	loadFont(m_font,fontName);
}

LuaFont::LuaFont( FontPtr originFont )
{
	if(originFont != NULL){
		m_font = originFont;
	}else{
		m_font = myGame->getFontManager()->createFont();
	}
}

int LuaFont::load(lua_State *state)
{
	if(lua_isstring(state,-1)){
		String fontResource = LUA_GET_STRING(-1);

		lua_pushboolean(state,loadFont(m_font,fontResource));
	}else{
		LuaManager::printError("Expected string argument.");

		lua_pushboolean(state,FALSE);
	}

	return 1;
}

int LuaFont::getSize(lua_State *state)
{
	lua_pushinteger(state,m_font->getSize());

	return 1;
}

int LuaFont::setSize(lua_State *state)
{
	if(lua_isnumber(state,-1)){
		int newSize = LUA_GET_INTEGER(-1);
		m_font->setSize(newSize);
	}else{
		LuaManager::printError("Expected integer argument.");
	}

	return 0;
}

int loadFont(FontPtr font,const String& fontName)
{
	font = myGame->getFontManager()->createFont(fontName);

	if(font->loadedSuccessful()){
		return TRUE;
	}else{
		LuaManager::printError("Could not load font \"" + fontName + "\"");
		return FALSE;
	}
}