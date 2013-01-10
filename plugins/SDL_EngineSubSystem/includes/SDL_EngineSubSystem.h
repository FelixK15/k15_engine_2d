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

#ifndef __CLASSNAME__
#define __CLASSNAME__

#include "StandardIncludes.h"
#include "IEngineSubSystem.h"

#include "SDL_GraphicManager.h"
#include "SDL_FontManager.h"
#include "SDL_MusicManager.h"
#include "SDL_MessageQueue.h"
#include "SDL_SoundManager.h"
#include "SDL_SystemManager.h"

namespace K15_Engine
{
	class SDL_EngineSubSystem : public IEngineSubSystem
	{
	public:

		SDL_EngineSubSystem(){};

		virtual ~SDL_EngineSubSystem(){};

		virtual bool initialize();

		virtual void shutdown();

		virtual AbstractGraphicManager* createGraphicManager()
		{
			return new SDL_GraphicManager();
		}

		virtual AbstractFontManager* createFontManager()
		{
			return new SDL_FontManager();
		}

		virtual AbstractMusicManager* createMusicManager()
		{
			return new SDL_MusicManager();
		}

		virtual AbstractMessageQueue* createInputManager()
		{
			return new SDL_MessageQueue();
		}

		virtual AbstractSoundManager* createSoundManager()
		{
			return new SDL_SoundManager();
		}

		virtual AbstractSystemManager* createSystemManager()
		{
			return new SDL_SystemManager();
		}

	};
}

K15_Engine::SDL_EngineSubSystem *createEngineSubSystem();

#endif //__CLASSNAME__