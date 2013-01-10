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
 * This is the class that loads maps that got created with the program Tiled.
 * Tiled is a QT based Tileeditor which you can download from http://www.mapeditor.org/
 */

#pragma once

#ifndef __CLASSNAME__
#define __CLASSNAME__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class GameWorld;
	class Resource;

	class K15ENGINE_API TiledGameWorldCreator
	{
	public:
		TiledGameWorldCreator(GameWorld &gameWorld,Resource *resource);

		bool create();

	private:

		GameWorld *m_gameWorld;
		Resource *m_resource;
	};
}

#endif //__CLASSNAME__