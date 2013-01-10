#include "SDL_SoundManager.h"
#include "SDL_Sound.h"
#include "Game.h"
#include "Log.h"

using namespace K15_Engine;

SDL_SoundManager::SDL_SoundManager()
{
	WRITE_DEBUG("SDL_SoundManager created.");
}

SDL_SoundManager::~SDL_SoundManager()
{
	WRITE_DEBUG("SDL_SoundManager destroyed.");
}

SoundPtr SDL_SoundManager::createSound()
{
	SoundPtr newSound = SoundPtr(new SDL_Sound());
	_addToSoundCache(newSound);

	return newSound;
}

SoundPtr SDL_SoundManager::createSound( Resource *resource )
{
	SoundPtr newSound = createSound();
	newSound->setContent(resource);

	return newSound;
}

SoundPtr SDL_SoundManager::createSound( const String& resourceName )
{
	Resource *res = myGame->getResourceManager()->getResource(resourceName);

	return createSound(res);
}

