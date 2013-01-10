/********************************************************************
	created:	2011/11/08
	created:	8:11:2011   1:34
	filename: 	SDL_Font.h
	author:		Felix Klinge
	
	purpose:	This Class is the an implementation of the abstract BaseFont
				class. This class represents a wrapper class for SDLs TTF_Font.
*********************************************************************/

#pragma once

#ifndef __SDL_FONT__
#define __SDL_FONT__

#include "StandardIncludes.h"
#include "IFont.h"
#include "Color.h"

//Some forward declaration
struct _TTF_Font;
typedef _TTF_Font TTF_Font;
struct SDL_RWops;
struct SDL_Surface;

namespace K15_Engine
{	
	class SDL_Font : public IFont
	{
	
	public:
		SDL_Font();
	
		virtual ~SDL_Font();

		virtual U8 getSize() const {return m_size;}

		virtual void setSize(U8 size){m_size = size;}

		virtual bool copyFrom(IResourceable *resourceable)
		{
			//not implemented yet.

			return false;
		}
	
		virtual bool setContent(Resource *resource);

		virtual bool loadedSuccessful(){return m_font != NULL;}

		TTF_Font *getFont() {return m_font;}
	
	private:
		
		//This method is a little workaround for properly graphical text representation
		void _fillGraphic(SDL_Surface *graphic,String text,Color &clr);
	
		TTF_Font *m_font;

		U8 m_size;
	};
}
#endif //__SDL_FONT__
