#pragma once

#ifndef __SDL_SOUNDMANAGERSUBSYSTEM__
#define __SDL_SOUNDMANAGERSUBSYSTEM__

#include "StandardIncludes.h"
#include "AbstractSoundManager.h"

namespace K15_Engine
{
	class SDL_SoundManager : public AbstractSoundManager
	{
	public:
		SDL_SoundManager();

		virtual ~SDL_SoundManager();

		virtual SoundPtr createSound();

		virtual SoundPtr createSound( Resource *resource );

		virtual SoundPtr createSound( const String& resourceName );

	};
}

#endif //__SDL_SOUNDMANAGERSUBSYSTEM__