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

#ifndef __LUA_EVENT__
#define __LUA_EVENT__

#include "StandardIncludes.h"
#include "Event.h"
#include "LuaAble.h"

namespace K15_Engine
{
	class LuaEvent : public LuaAble<LuaEvent>
	{
	public:

		LuaEvent(const String& eventname);

		LuaEvent(const Event& originEvent);

		int fire(lua_State *stae);

		int addToQueue(lua_State *state);

		int getArgument(lua_State *state);

		int getType(lua_State *state);

		int setArgument(lua_State *state);

		Event& getEvent(){return m_event;}

		static LuaAble<LuaEvent>::LuaCFunction m_functions[];

	private:

		Event m_event;
	};
}

#endif //__CLASSNAME__