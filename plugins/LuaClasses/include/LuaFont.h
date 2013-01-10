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

#ifndef __LUAFONT__
#define __LUAFONT__

#include "StandardIncludes.h"
#include "LuaAble.h"

namespace K15_Engine
{
	class LuaFont : public LuaAble<LuaFont>
	{
	public:
		LuaFont();

		LuaFont(const String& fontName);

		LuaFont(FontPtr originFont);

		int load(lua_State *state);

		int setSize(lua_State *state);

		int getSize(lua_State *state);

		FontPtr getFont(){return m_font;}

		static LuaAble<LuaFont>::LuaCFunction m_functions[];

	private:
		FontPtr m_font;
	};
}

#endif //__CLASSNAME__