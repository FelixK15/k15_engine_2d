///////////////////////////////////////////////////////////
//  SDL_Sound.cpp
//  Implementation of the Class SDL_Sound
//  Created on:      16-Aug-2011 20:59:39
//  Original author: klf
///////////////////////////////////////////////////////////

#include "SDL_Sound.h"
#include "Resource.h"
#include "Log.h"

#include "SDL_mixer\SDL_mixer.h"

using namespace K15_Engine;

SDL_Sound::SDL_Sound()
{
	m_chunk = NULL;
}

SDL_Sound::~SDL_Sound()
{
	if(m_chunk != NULL){
		Mix_FreeChunk(m_chunk);
		m_chunk = NULL;
	}
}

bool SDL_Sound::play()
{
	return play(1);
}

bool SDL_Sound::play(int times)
{
	if(m_chunk == NULL){
		WRITE_ERRORLOG("There's no sound to play.");
		return false;
	}

	int result = Mix_PlayChannel(-1,m_chunk,times);
	if(result == -1){
		WRITE_ERRORLOG("Error while playing sound. (" + String(Mix_GetError()) + ")");
		return false;
	}

	m_channel = result;
	return true;
}

void SDL_Sound::stop()
{
	if(m_chunk == NULL){
		WRITE_ERRORLOG("There's no sound to stop.");
		return;
	}
	Mix_HaltChannel(m_channel);
	return;
}

bool SDL_Sound::setContent(Resource *resource)
{
	Mix_Chunk *newChunk = Mix_LoadWAV_RW(SDL_RWFromMem(static_cast<void*>(resource->getContent()),resource->getSize()),1);
	if(newChunk != NULL){
		if(m_chunk != NULL){
			Mix_FreeChunk(m_chunk);
			m_chunk = NULL;
		}
		
		m_chunk = newChunk;

		return true;
	}

	WRITE_ERRORLOG("Couldn't not load new sound. (" + String(Mix_GetError()) + ")");
	return false;
}