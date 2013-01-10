#include "SDL_FontManager.h"
#include "SDL_Font.h"
#include "Game.h"
#include "Log.h"

#include "SDL_ttf\SDL_ttf.h"

using namespace K15_Engine;

SDL_FontManager::SDL_FontManager()
{
	WRITE_DEBUG("SDL_FontManager has been created.");
}

SDL_FontManager::~SDL_FontManager()
{
	WRITE_DEBUG("SDL_FontManager has been destroyed.");
}

FontPtr K15_Engine::SDL_FontManager::createFont()
{
	FontPtr newFont(new SDL_Font());
	m_fonts.push_back(newFont);
	return newFont;
}

FontPtr K15_Engine::SDL_FontManager::createFont( const String &resourceName,U8 size )
{
	Resource *res = myGame->getResourceManager()->getResource(resourceName);

	return createFont(res,size);
}

FontPtr SDL_FontManager::createFont( Resource *resource, U8 size)
{	
	//If the given resource is empty, any following cpu cycle would be a waste of cpu power.
	if(resource == NULL){
		WRITE_CRITICALLOG("Given resource is empty.");
		return NULL;
	}

	FontPtr newFont = createFont();
	newFont->setSize(size);

	if(!newFont->setContent(resource)){
		WRITE_CRITICALLOG("Couldn't load font. (" + resource->getName() + " | " +String(TTF_GetError()) + ")");
		return NULL;
	}

	return newFont;
}

bool K15_Engine::SDL_FontManager::initialize()
{
	if(TTF_Init() == -1){
		WRITE_CRITICALLOG("SDL_ttf initialization failed. (" + String(TTF_GetError()) + ")");
		return false;
	}

	WRITE_DEBUG("SDL_ttf has been initialized.");

	return true;
}

void K15_Engine::SDL_FontManager::shutdown()
{
	//Release Resources from each font. (Error will get thrown if they'll get deleted after TTF_Quit had been called)
	for(FontList::iterator i = m_fonts.begin();i != m_fonts.end();i++){
		(*i)->~IFont();
	}

	m_fonts.clear();
	TTF_Quit();

	WRITE_DEBUG("SDL_ttf has been shutdown.");
}
