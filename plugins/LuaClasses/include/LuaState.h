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

#ifndef __LUASTATE__
#define __LUASTATE__

#include "StandardIncludes.h"
#include "LuaAble.h"
#include "IState.h"

namespace K15_Engine
{
	class LuaState : public LuaAble<LuaState>, public IState
	{
	public:
		LuaState();

		virtual bool start();

		virtual void update(U32 deltaTime);

		virtual void end();

		static LuaAble<LuaState>::LuaCFunction m_functions[];
	};
}

#endif //__LUASTATE__