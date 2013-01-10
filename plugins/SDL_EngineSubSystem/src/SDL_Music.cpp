///////////////////////////////////////////////////////////
//  SDL_Music.cpp
//  Implementation of the Class SDL_Music
//  Created on:      16-Aug-2011 20:59:46
//  Original author: klf
///////////////////////////////////////////////////////////

#include "SDL_Music.h"
#include "Resource.h"
#include "Log.h"

#include "SDL_mixer\SDL_mixer.h"

using namespace K15_Engine;

SDL_Music::SDL_Music()
{
	m_music = NULL;
}

SDL_Music::~SDL_Music()
{
	if(m_music != NULL){
		Mix_FreeMusic(m_music);
		m_music = NULL;
	}
}

void SDL_Music::pause()
{
	if(m_music == NULL){
		WRITE_ERRORLOG("Couldn't pause music because no music has been set,yet.");
		return;
	}

	Mix_HaltMusic();
	return;
}

bool SDL_Music::start(int loops)
{
	if(m_music == NULL){
		WRITE_ERRORLOG("Couldn't start music because no music has been set,yet.");
		return false;
	}

	if(Mix_PlayMusic(m_music,loops) != 0){
		WRITE_ERRORLOG("Couldn't start music. (" + String(Mix_GetError()) + ")");
		return false;
	}
	return true;
}

bool SDL_Music::start(int loops, int ms)
{
	if(m_music == NULL){
		WRITE_ERRORLOG("Couldn't start music because no music has been set,yet.");
		return false;
	}

	if(Mix_FadeInMusic(m_music,loops,ms) != 0){
		WRITE_ERRORLOG("Couldn't start music. (" + String(Mix_GetError()) + ")");
		return false;
	}
	return true;
}

void SDL_Music::stop()
{
	if(m_music == NULL){
		WRITE_ERRORLOG("Couldn't stop music because no music has been set,yet.");
		return;
	}

	stop(0);
	return;
}

void SDL_Music::stop(int ms)
{
	Mix_FadeOutMusic(ms);
}

bool SDL_Music::setContent( Resource *resource )
{
	Mix_Music *newMusic = Mix_LoadMUS_RW(SDL_RWFromMem(static_cast<void*>(resource->getContent()),resource->getSize()));
	if(newMusic != NULL){
		if(m_music != NULL){
			Mix_FreeMusic(m_music);
			m_music = NULL;
		}
		m_music = newMusic;

		return true;
	}
	WRITE_ERRORLOG("Couldn't set new music. (" + String(Mix_GetError()) + ")");
	return false;
}

bool SDL_Music::isRunning()
{
	return Mix_PlayingMusic() == 1;
}