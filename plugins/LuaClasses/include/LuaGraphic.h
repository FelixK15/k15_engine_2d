/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * 
 */
#pragma once

#ifndef __LUAGRAPHIC__
#define __LUAGRAPHIC__

#include "StandardIncludes.h"
#include "LuaAble.h"

namespace K15_Engine
{
	class LuaGraphic : public LuaAble<LuaGraphic>
	{
	public:

		LuaGraphic();

		LuaGraphic(GraphicPtr originGraphic);
		
		LuaGraphic(const String& resource);

		int rotate(lua_State *state);

		int load(lua_State *state);

		int setColorkey(lua_State *state);

		int isLocked(lua_State *state);

		int getAlpha(lua_State *state);

		int setPosition(lua_State *state);

		int setSize(lua_State *state);

		int setVisible(lua_State *state);

		int attachToScreen(lua_State *state);

		int detachFromScreen(lua_State *state);

		int isScreenAttached(lua_State *state);

		int isVisible(lua_State *state);

		int getSize(lua_State *state);

		int getPosition(lua_State *state);

		int setPixel(lua_State *state);

		int fillWithColor(lua_State *state);

		int getPixel(lua_State *state);

		int cutRect(lua_State *state);

		int setDrawOutOfBounds(lua_State *state);

		int drawOutOfBounds(lua_State *state);

		int draw(lua_State *state);

		GraphicPtr getGraphic(){return m_graphic;}

		static LuaAble<LuaGraphic>::LuaCFunction m_functions[];

	private:
		GraphicPtr m_graphic;
	};
}

#endif //__LUAGRAPHIC__