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
 * Abstract Basic State class for GameWorld States.
 */
#pragma once

#ifndef __GameWorldState__
#define __GameWorldState__

#include "IState.h"

namespace K15_Engine
{
	class GameWorld;

	class K15ENGINE_API GameWorldState	: public IState
	{
	public:

		GameWorldState();

		~GameWorldState();

		virtual void update(U32 deltaTime);

		bool setGameWorld(GameWorld gameworld);

	private:
		GameWorld *m_gameworld;


	};
}

#endif //__CLASSNAME__