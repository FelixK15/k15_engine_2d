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

#ifndef __LUAGAMEOBJECT__
#define __LUAGAMEOBJECT__

#include "StandardIncludes.h"
#include "GameObject.h"
#include "LuaAble.h"

int luaopen_LuaGameObject(lua_State *state);

namespace K15_Engine
{
	class LuaGameObject : public LuaAble<LuaGameObject>
	{

	public:

		LuaGameObject();

		LuaGameObject(const String &type);

		LuaGameObject(const GameObject&);

		virtual ~LuaGameObject();

		int getID(lua_State *state);

		int getType(lua_State *state);

		int setType(lua_State *state);

		int setNextState(lua_State *state);

		int setPosition(lua_State *state);

		int setPositionNextTick(lua_State *state);

		int setSize(lua_State *state);

		int setSizeNextTick(lua_State *state);

		int setAngle(lua_State *state);

		int setAngleNextTick(lua_State *state);

		int autoUpdate(lua_State *state);

		int getAngle(lua_State *state);

		int getPosition(lua_State *state);

		int getSize(lua_State *state);

		int restorePosition(lua_State *state);

		int restoreSize(lua_State *state);

		int restoreAngle(lua_State *state);

		int addComponent(lua_State *state);

		int removeComponent(lua_State *state);

		int broadcastMessage(lua_State *state);

		int update(lua_State *state);

		int setDebugMode(lua_State *state);

		GameObject *getGameObject() {return &m_gameObject;}

		static LuaAble<LuaGameObject>::LuaCFunction m_functions[];

		static int create(lua_State *state);

	private:
		GameObject m_gameObject;
	};
}

#endif //__CLASSNAME__