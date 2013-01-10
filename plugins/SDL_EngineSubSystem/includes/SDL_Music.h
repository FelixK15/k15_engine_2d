///////////////////////////////////////////////////////////
//  SDL_Music.h
//  Implementation of the Class SDL_Music
//  Created on:      16-Aug-2011 20:59:46
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#pragma once

#ifndef __SDL_MUSIC__
#define __SDL_MUSIC__

#include "StandardIncludes.h"
#include "IMusic.h"

struct _Mix_Music;
typedef _Mix_Music Mix_Music;

namespace K15_Engine
{
	class SDL_Music : public IMusic
	{

	public:
		SDL_Music();

		~SDL_Music();

		virtual void pause();

		virtual bool isRunning();

		virtual bool start(int loops);

		virtual bool start(int loops, int ms);

		virtual void stop();

		virtual void stop(int ms);

		virtual bool setContent(Resource *resource);

		virtual bool loadedSuccessful(){return m_music != NULL;}

		virtual bool copyFrom(IResourceable *resourceable)
		{
			//not implemented yet.

			return false;
		}

	private:
		Mix_Music *m_music;

	};
}

#endif // __SDL_MUSIC__
