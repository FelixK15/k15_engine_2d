#include "SDL_Font.h"
#include "ResourceManager.h"
#include "Log.h"

#include "SDL\SDL_rwops.h"
#include "SDL_ttf\SDL_ttf.h"

using namespace K15_Engine;

SDL_Font::SDL_Font()
{
	m_font = NULL;
}

SDL_Font::~SDL_Font()
{
	if(m_font){
		TTF_CloseFont(m_font);
		m_font = NULL;
	}
}

bool SDL_Font::setContent( Resource *resource )
{
	//If theres already a font being loaded, it will get deleted.
	if(m_font){
		TTF_CloseFont(m_font);
		m_font = NULL;
	}
	
	//New font gets loaded.
	m_font = TTF_OpenFontRW(SDL_RWFromMem(static_cast<void*>(resource->getContent()),resource->getSize()),1,m_size);

	return m_font != NULL;
}

void SDL_Font::_fillGraphic( SDL_Surface *graphic,String text,Color &clr )
{
	SDL_Color sdlcolor;
	sdlcolor.r = clr.getR();
	sdlcolor.g = clr.getG();
	sdlcolor.b = clr.getB();

	graphic = TTF_RenderUTF8_Solid(m_font,text.c_str(),sdlcolor);
}