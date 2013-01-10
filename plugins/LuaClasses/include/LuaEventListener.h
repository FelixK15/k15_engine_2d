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

#ifndef __LUA_EVENT_LISTENER__
#define __LUA_EVENT_LISTENER__

#include "StandardIncludes.h"
#include "LuaAble.h"
#include "IEventListener.h"

namespace K15_Engine
{
	class LuaEventListener : public LuaAble<LuaEventListener>, public IEventListener
	{
	public:
		LuaEventListener();

		LuaEventListener(const String& eventName);

		virtual ~LuaEventListener();

		int setEvent(lua_State *state);

		int getEvent(lua_State *state);

		virtual bool handleEvent(Event const &gameEvent);

		static LuaAble<LuaEventListener>::LuaCFunction m_functions[];

	private:
		Event m_event;
	};
}

#endif //__CLASSNAME__