#pragma once

#ifndef __SDL_WINDOW__
#define __SDL_WINDOW__

#include "StandardIncludes.h"
#include "AbstractWindow.h"

struct SDL_Surface; 

namespace K15_Engine
{	
	class SDL_Window : public AbstractWindow
	{
	
	public:
		SDL_Window(int width,int height,int bpp,bool fullscreen,const String& caption);
	
		virtual ~SDL_Window();
	
		virtual bool create();
	
		virtual void destroy();
	
		virtual bool swapBuffers();
	
		virtual void setCaption(const String& caption);
	
	private:

		SDL_Surface *m_screen;
	};
}

#endif //__SDL_WINDOW__