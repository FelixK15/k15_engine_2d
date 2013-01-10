/********************************************************************
	created:	2011/11/08
	created:	8:11:2011   1:27
	filename: 	SDL_Graphic.h
	author:		Felix Klinge
	
	purpose:	This Class is the an implementation of the abstract BaseGraphic
				class. This class represents a wrapper class for SDLs SDL_Surface.
*********************************************************************/

#pragma once

#ifndef __SDL_GRAPHIC__
#define __SDL_GRAPHIC__

#include "StandardIncludes.h"
#include "AbstractGraphic.h"

struct SDL_Rect;
struct SDL_Surface;

namespace K15_Engine
{	
	class SDL_Graphic : public AbstractGraphic
	{

	public:
		SDL_Graphic();
	
		~SDL_Graphic();

		virtual void unlock();

		virtual void lock();
	
		virtual bool rotate(F32 angle);
	
		virtual bool zoom(F32 zoomX,F32 zoomY);
	
		virtual bool shrink(U16 shrinkX,U16 shrinkY);
	
		virtual bool fillWithColor(const Color &color);
	
		virtual bool setColorkey(U8 r,U8 g,U8 b);
	
		virtual bool setColorkey(const Color &colorkey);
	
		virtual bool setAlpha(U8 alphaValue);

		virtual void restoreOriginal();

		virtual bool setPixel(const Position &position,const Color &pixel);

		virtual const Color getPixel(const Position &position);
	
		virtual GraphicPtr cutRect(const Position &position,const Size &size );

		virtual bool copyFrom(IResourceable *otherGraphic);

		virtual void setSize( const Size &size );

		virtual void setSize( U16 w,U16 h ){setSize(Size(w,h));}
	
		virtual bool setContent(Resource *resource);

		virtual bool loadedSuccessful(){return m_graphic != NULL;}

		virtual bool drawAt(GraphicPtr graphic,const Position& position);

		virtual void setGraphicAsOrigin();

		bool setGraphic(SDL_Surface *newSurface,bool eraseSrcSurface, bool onOriginalGraphic = false);

		SDL_Surface *getGraphic() {return m_graphic;}

		SDL_Surface *getOriginalGraphic() {return m_originalGraphic;}
	
	private:

		bool _fitSize();

		SDL_Surface *m_graphic;

		SDL_Surface *m_originalGraphic;
	
		// TODO Resize the Surface after each change of the rectangular [5/12/2011 Felix]
	};
}
#endif //__SDL_GRAPHIC__
