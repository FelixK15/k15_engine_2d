#include "SDL_MusicManager.h"
#include "SDL_Music.h"
#include "Game.h"
#include "Log.h"

#include "SDL_mixer\SDL_mixer.h"

using namespace K15_Engine;

SDL_MusicManager::SDL_MusicManager()
{
	WRITE_DEBUG("SDL_MusicManager created.");
}

SDL_MusicManager::~SDL_MusicManager()
{
	WRITE_DEBUG("SDL_MusicManager deleted.");
}

bool SDL_MusicManager::initialize()
{
	if(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == -1 || Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,4096) == -1){
		WRITE_CRITICALLOG("Could not initialize SDL_MusicManager. (" + String(Mix_GetError()) + ")");
		return false;
	}

	WRITE_DEBUG("SDL_MusicManager has been initialized.");

	return true;
}

MusicPtr SDL_MusicManager::createMusic()
{
	MusicPtr newMusic = MusicPtr(new SDL_Music());
	_addToMusicCache(newMusic);

	return newMusic;
}

MusicPtr SDL_MusicManager::createMusic( Resource *resource )
{
	MusicPtr newMusic = createMusic();

	newMusic->setContent(resource);

	return newMusic;
}

MusicPtr SDL_MusicManager::createMusic( const String& resourceName )
{
	Resource *res = myGame->getResourceManager()->getResource(resourceName);

	return createMusic(res);
}

void SDL_MusicManager::shutdown()
{
	Mix_CloseAudio();
	Mix_Quit();
	
	WRITE_DEBUG("SDL_MusicManager has been shutdown.");
}