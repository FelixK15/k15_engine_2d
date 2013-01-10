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
 * Debug class that provides function for debug purposes
 */
#pragma once

#ifndef __K15__DEBUG__
#define __K15__DEBUG__

#include "StandardIncludes.h"
#include "DrawableString.h"

namespace K15_Engine
{
	typedef std::list<DrawableString> DebugStringList;

	class K15ENGINE_API Debug
	{
	public:

		static void update(U32 deltaTime);

		static void drawAlignedDebugString(const String& string);

		static const int NEXT_FREE_ID;

		static bool activated;
	};
}

#endif //__K15__DEBUG__