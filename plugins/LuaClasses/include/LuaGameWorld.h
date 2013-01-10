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

#ifndef __LUAGAMEWORLD__
#define __LUAGAMEWORLD__

#include "StandardIncludes.h"
#include "GameWorld.h"
#include "LuaAble.h"

namespace K15_Engine
{
	class LuaGameWorld : public LuaAble<LuaGameWorld>
	{
	public:

		LuaGameWorld();

		LuaGameWorld(const String& resource);

		LuaGameWorld(GameWorld& originGameWorld);

		//example lua call: name = gameworld.getName();
		int getName(lua_State *state);

		//example lua call: number = gameworld.addLayer(gameworldlayer); 
		int addLayer(lua_State *state);

		//example lua call: bool = gameworld.removeLayer(layerindex); or bool = gameworld.removelayer(layername);
		int removeLayer(lua_State *state);

		//example lua call: bool = gameworld.addGameObject(gameobject,-1); or bool = gameworld.addGameObject(gameobject,layername);
		int addGameObject(lua_State *state);

		GameWorld& getGameWorld(){return m_gameWorld;}

		static LuaAble<LuaGameWorld>::LuaCFunction m_functions[];

	private:

		GameWorld m_gameWorld;
	};
}

#endif //__LUAGAMEWORLD__