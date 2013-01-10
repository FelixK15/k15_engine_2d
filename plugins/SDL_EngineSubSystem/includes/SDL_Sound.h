///////////////////////////////////////////////////////////
//  SDL_Sound.h
//  Implementation of the Class SDL_Sound
//  Created on:      16-Aug-2011 20:59:39
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#ifndef __SDL_SOUND__
#define __SDL_SOUND__

#include "StandardIncludes.h"
#include "AbstractSound.h"

struct Mix_Chunk;

namespace K15_Engine
{
	class SDL_Sound : public AbstractSound
	{

	public:
		SDL_Sound();

		~SDL_Sound();

		virtual bool play();

		virtual bool play(int times);

		virtual void stop();

		virtual bool setContent(Resource *resource);

		virtual bool loadedSuccessful(){return m_chunk != NULL;}

		virtual bool copyFrom(IResourceable *resourceable)
		{
			//Not implemented yet.

			return false;
		}

	private:
		Mix_Chunk *m_chunk;
		int m_channel;

	};
}

#endif // __SDL_SOUND__
