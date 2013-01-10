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
 * Class that can be used to execute lua commands.
 */
#pragma once

#ifndef __LUACOMMAND__
#define __LUACOMMAND__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API LuaCommand
	{
	public:
		LuaCommand(const String& command);

		bool execute();

		bool executedSuccessful(){return m_executedSuccessful;}

		const String getErrorMessage(){return m_errorMessage;}

	private:

		const String m_command;

		String m_errorMessage;

		bool m_executedSuccessful;
	};
}

#endif //__LUACOMMAND__