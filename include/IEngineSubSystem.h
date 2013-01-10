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

#ifndef __ENGINE_SUBSYSTEM_
#define __ENGINE_SUBSYSTEM_

#include "StandardIncludes.h"

namespace K15_Engine
{
	class AbstractGraphicManager;
	class AbstractFontManager;
	class AbstractMusicManager;
	class AbstractMessageQueue;
	class AbstractSoundManager;
	class AbstractSystemManager;

	class K15ENGINE_API IEngineSubSystem
	{
	public:

		virtual bool initialize() = 0;

		virtual void shutdown() = 0;

		virtual AbstractGraphicManager* createGraphicManager() = 0;

		virtual AbstractFontManager* createFontManager() = 0;

		virtual AbstractMusicManager* createMusicManager() = 0;

		virtual AbstractMessageQueue* createInputManager() = 0;

		virtual AbstractSoundManager* createSoundManager() = 0;

		virtual AbstractSystemManager* createSystemManager() = 0;
	};
}

#endif //__ENGINE_SUBSYSTEM_