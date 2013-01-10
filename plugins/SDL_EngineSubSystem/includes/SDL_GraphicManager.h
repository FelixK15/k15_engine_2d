/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * 
 */
#pragma once

#ifndef __SDL_GRAPHICMANAGER__
#define __SDL_GRAPHICMANAGER__

#include "StandardIncludes.h"
#include "AbstractGraphicManager.h"

struct SDL_Surface;

namespace K15_Engine
{
	class SDL_GraphicManager : public AbstractGraphicManager
	{

	public:

		SDL_GraphicManager();

		virtual ~SDL_GraphicManager();

		virtual bool initialize();

		virtual void shutdown();

		virtual GraphicPtr createGraphic(); 

		virtual GraphicPtr createGraphic( const String &resourceName );

		virtual GraphicPtr createGraphic( const Circle& circle, const Position& position = Position(0,0 ) , const Color& color = Color::Black, bool fill = true);

		virtual GraphicPtr createGraphic( const Line& line, const Position& position = Position(0,0 ) , const Color& color = Color::Black );

		virtual GraphicPtr createGraphic( const Size& size, const Position& position = Position(0,0 ) , const Color& color = Color::Black, bool fill = true);

		virtual GraphicPtr createGraphic( const Ellipse& ellipse, const Position& position = Position(0,0 ) , const Color& color = Color::Black, bool fill = true);

		virtual GraphicPtr createGraphic( Resource *resource );

		virtual GraphicPtr createGraphic( char character, FontPtr font, const Position& position,const Color& color );

		virtual bool drawShapedGraphic( const Size& size, const Position& position = Position(0,0 ) , const Color& color = Color::Black, bool fille = true);

		virtual AbstractWindow* createWindow(int width,int height,int bpp,bool fullscreen,const String& caption);

		virtual bool draw( GraphicPtr graphic,Camera *camera );

	private:

		SDL_Surface* m_screenSurface;

	};
}

#endif //__SDL_GRAPHICMANAGER__