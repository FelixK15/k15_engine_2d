#include "SDL_EngineSubSystem.h"
#include "Log.h"

#include "SDL\SDL.h"

using namespace K15_Engine;

SDL_EngineSubSystem *createEngineSubSystem()
{
	return new SDL_EngineSubSystem();
}

bool SDL_EngineSubSystem::initialize()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1){
		WRITE_CRITICALLOG("SDL could not get initialized.  (" + String(SDL_GetError()) + ")");
		return false;
	}

	WRITE_DEBUG("SDL has been initialized successfully.");
	SDL_EnableUNICODE(1);
	return true;
}

void SDL_EngineSubSystem::shutdown()
{
	SDL_Quit();
}