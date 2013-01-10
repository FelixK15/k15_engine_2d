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

#ifndef __LUAGAMEWORLDLAYER__
#define __LUAGAMEWORLDLAYER__

#include "StandardIncludes.h"
#include "GameWorldLayer.h"
#include "LuaAble.h"

namespace K15_Engine
{
	class LuaGameWorldLayer : public LuaAble<LuaGameWorldLayer>
	{
	public:
		LuaGameWorldLayer();

		LuaGameWorldLayer(const String& name);

		LuaGameWorldLayer(GameWorldLayer& originLayer);

		int getName(lua_State *state);

		int setName(lua_State *state);

		int isCollisionLayer(lua_State *state);

		int setAsCollisionLayer(lua_State *state);

		int getScrollSpeed(lua_State *state);

		int setScrollSpeed(lua_State *state);

		int addGameObject(lua_State *state);

		GameWorldLayer& getGameWorldLayer(){return m_layer;}

		static LuaAble<LuaGameWorldLayer>::LuaCFunction m_functions[];

	private:

		GameWorldLayer m_layer;
	};
}

#endif //__LUAGAMEWORLDLAYER__