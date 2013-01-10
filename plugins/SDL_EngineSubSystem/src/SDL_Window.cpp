#include "SDL_Window.h"
#include "SDL_Graphic.h"
#include "ResourceManager.h"
#include "StringConverter.h"
#include "Log.h"
#include "SDL\SDL_video.h"

using namespace K15_Engine;

SDL_Window::SDL_Window(int width,int height,int bpp,bool fullscreen,const String& caption)
	: AbstractWindow(width,height,bpp,fullscreen,caption)
{
	m_screen = NULL;
}

SDL_Window::~SDL_Window()
{

}

bool SDL_Window::create()
{
	U32 flags = 0;
	if(m_fullscreen)
		flags = SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
	else
		flags = SDL_SWSURFACE | SDL_DOUBLEBUF;

	setCaption(m_caption);

	m_screen = SDL_SetVideoMode(m_size.getWidth(),m_size.getHeight(),m_bpp,flags);
	if(m_screen){
		WRITE_LOG("SDL Window has been successfully created.(" + 
			StringConverter::toString(m_size.getWidth()) + "x" + StringConverter::toString(m_size.getHeight()) + "x" +
			StringConverter::toString(m_bpp) +")");
		return true;
	}else{
		WRITE_CRITICALLOG("SDL Window creation failed. (" + String(SDL_GetError()) + ")");
		return false;
	}
}

void SDL_Window::destroy()
{
	m_screen = NULL;
	WRITE_LOG("SDL Window has been shut down.");
}

bool SDL_Window::swapBuffers()
{
	if(SDL_Flip(m_screen) == 0){
		SDL_Surface *background = SDL_CreateRGBSurface(0,m_size.getWidth(),m_size.getHeight(),m_bpp,0,0,0,0);
		SDL_FillRect(background,NULL,0x000000);
		SDL_BlitSurface(background,NULL,m_screen,NULL);
		SDL_FreeSurface(background);
		return true;
	}

	WRITE_CRITICALLOG("Buffer swapping failed. (" + String(SDL_GetError()) + ")");
	return false;
}

void SDL_Window::setCaption( const String& caption )
{
	SDL_WM_SetCaption(caption.c_str(),NULL);
	m_caption = caption;
}
