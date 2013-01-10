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
 * This is a builder that is responsible for 
 * creating GameWorld's
 */
#pragma once

#ifndef __GAMEWORLDFACTORY__
#define __GAMEWORLDFACTORY__

#include "StandardIncludes.h"
#include "GameWorld.h"

namespace K15_Engine
{
	class Resource;

	class K15ENGINE_API GameWorldFactory
	{
	public:

		/**
		* Creates a new GameWorld object. Once the method is done, the GameWorldReady Event will get fired.
		*
		* @param  res - Resource from which the GameWorld will get created.
		* The method will decide which concrete GameWorldCreator will get used for the creation
		*
		* @return GameWorld - GameWorld object that has been created.
		*/
		static bool createWorld(GameWorld& gameWorld,Resource *res);

	private:
		GameWorldFactory(){} // No one can intantiate me muhahahah
	};
}

#endif //__CLASSNAME__