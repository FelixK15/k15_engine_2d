#pragma once

#ifndef __SDL_MUSICMANAGERSUBSYSTEM__
#define __SDL_MUSICMANAGERSUBSYSTEM__

#include "StandardIncludes.h"
#include "AbstractMusicManager.h"

namespace K15_Engine
{
	class SDL_MusicManager : public AbstractMusicManager
	{
	public:
		SDL_MusicManager();

		virtual ~SDL_MusicManager();

		virtual bool initialize();

		virtual void shutdown();

		virtual MusicPtr createMusic();

		virtual MusicPtr createMusic(Resource *resource);

		virtual MusicPtr createMusic(const String& resourceName);

	};
}

#endif //__SDL_MUSICMANAGERSUBSYSTEM__