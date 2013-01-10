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
 * Interface for the class BaseGraphic.
 */

#pragma once

#ifndef __IGRAPHIC__
#define __IGRAPHIC__

#include "StandardIncludes.h"

#include "Rectangle.h"
#include "Color.h"
#include "IResourceable.h"

namespace K15_Engine
{
	class K15ENGINE_API IGraphic : public IResourceable
	{

	public:

 		/**
 		* Destructor just for auto_ptr compatibility.
 		*/
 		virtual ~IGraphic(){};

		/**
		*
		* Is the graphic locked?
		*
		* @return bool
		*/
		virtual bool isLocked() const = 0;

		/**
		*
		* Unlock the graphic to make pixel manipulation possible.
		*
		*/
		virtual void unlock() = 0;

		/**
		*
		* Lock the graphic to avoid pixel manipulation.
		*
		*/
		virtual void lock() = 0;

		/**
		*
		* Restore original graphic (Original graphic is the unchanged original image that has been loaded)
		*
		*/
		virtual void restoreOriginal() = 0;

		/**
		*
		* Rotates the graphic by a specific angle.
		*
		* @param  angle
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool rotate(F32 angle) = 0;
	
		/**
		*
		* Zooms the graphic by specific coordinates.
		*
		* @param  zoomX
		* @param  zoomY
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool zoom(F32 zoomX,F32 zoomY) = 0;
	
		/**
		*
		* Shrinks the graphic by specific coordinates.
		*
		* @param  shrinkX
		* @param  shrinkY
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool shrink(U16 shrinkX,U16 shrinkY) = 0;
	
		/**
		*
		* Fills the graphic with the information of the given Color object.
		*
		* @param  color - Color object which holds the information on which color should be used to fill the graphic.
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool fillWithColor(const Color &color) = 0;

		/**
		*
		* Fills the graphic with the give r,g,b,a values.
		*
		* @param  r - Red part of the color the graphic shall be filled with
		* @param  g - Green part of the color the graphic shall be filled with
		* @param  b - Blue part of the color the graphic shall be filled with
		* @param  a - Alpha (Transparency) part of the color the graphic shall be filled with
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool fillWithColor(U8 r,U8 g,U8 b,U8 a) = 0;
	
		/**
		*
		* Sets the colorkey (transparency color) by the given color values.
		*
		* @param  r - Red part of the color that shall get transparent
		* @param  g - Green part of the color that shall get transparent
		* @param  b - Blue part of the color that shall get transparent
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool setColorkey(U8 r,U8 g,U8 b) = 0;
	
		/**
		*
		* Sets the colorkey (transparency color) using the given Color object.
		*
		* @param  colorkey - Color object which holds the information on which color shall get transparent.
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool setColorkey(const Color &colorkey) = 0;

		/**
		*
		* Sets a pixel at a given position (determined by the Position object) to a specific color (determined by the Color object)
		* (graphic needs to get unlocked in order to enable pixel manipulation)
		*
		* @param  position - Position object which holds the position of the pixel that shall get set.
		* @param  pixel - Pixel object which holds the information of the pixel that shall get set.
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool setPixel(const Position &position,const Pixel &pixel) = 0;

		/**
		*
		* Sets a pixel at a given position (determined by the x and y coordinates) to a specific color (determined by the Color object)
		* (graphic needs to get unlocked in order to enable pixel manipulation)
		*
		* @param  x - x coordinate from the position of the pixel that shall get set.
		* @param  y - y coordinate from the position of the pixel that shall get set.
		* @param  pixel - Pixel object which holds the information of the pixel that shall get set.
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool setPixel(S16 x,S16 y,const Pixel &pixel) = 0;

		/**
		*
		* Sets a pixel at a given position (determined by the x and y coordinates) to a specific color (determined by the r,g,b,a values)
		* (graphic needs to get unlocked in order to enable pixel manipulation)
		*
		* @param  x - x coordinate from the position of the pixel that shall get set.
		* @param  y - y coordinate from the position of the pixel that shall get set.
		* @param  r - Red part from the color of the pixel that shall get set.
		* @param  g - Green part from the color of the pixel that shall get set.
		* @param  b - Blue part from the color of the pixel that shall get set.
		* @param  a - Alpha (Transparency) part from the color of the pixel that shall get set.
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool setPixel(S16 x,S16 y,U8 r,U8 g,U8 b,U8 a) = 0;
	
		/**
		*
		* Sets the transparency of the graphic to a specific value (alpha).
		* 255 = invisible
		* 0 = visible
		*
		* @param  alphaValue - Transparency value
		*
		* @return bool - true if successful and false if not.
		*/
		virtual bool setAlpha(U8 alphaValue) = 0;
	
		/**
		*
		* Sets the position of the graphic
		*
		* @param  x - x coordinate
		* @param  y - y coordinate
		*
		*/
		virtual void setPosition(S16 x,S16 y) = 0;

		/**
		*
		* Sets the position of the graphic
		*
		* @param  position - Position object which holds the x and y coordinates
		*
		*/
		virtual void setPosition(const Position &position) = 0;
	
		/**
		*
		* Sets the size of the graphic. (graphic will NOT get scaled in the process,yet)
		*
		* @param  w - Width
		* @param  h - Height
		*
		*/
		virtual void setSize(U16 w,U16 h) = 0;

		/**
		*
		* Sets the size of the graphic. (graphic will NOT get scaled in the process,yet)
		*
		* @param  size - Size object which holds the new width and height values.
		*
		*/
		virtual void setSize(const Size &size) = 0;
	
		/**
		*
		* Returns the size of the graphic.
		*
		* @param  w - Pointer to a U16 variable in which the current width of the graphic will get saved.
		* @param  h - Pointer to a U16 variable in which the current height of the graphic will get saved.
		*
		*/
		virtual void getSize(U16 *w,U16 *h) const = 0;

		/**
		*
		* Returns the size of the graphic.
		*
		* @return Size - Size object which holds the width and height informations.
		*/
		virtual const Size getSize() const = 0;
	
		/**
		*
		* Returns the position of the graphic.
		*
		* @param  x - Pointer to a U16 variable in which the current x coordinate of the graphic will get saved.
		* @param  y - Pointer to a U16 variable in which the current y coordinate of the graphic will get saved.
		*
		*/
		virtual void getPosition(S16 *x,S16 *y) const = 0;

		/**
		*
		* Returns the position of the graphic.
		*
		* @return Position - Position object which holds the x and y coordinate of the graphic.
		*/
		virtual const Position getPosition() const = 0;
	
		/**
		*
		* Returns a pixel of the graphic.
		*
		* @param  x - x coordinate of the pixel that shall be returned.
		* @param  y - y coordinate of the pixel that shall be returned.
		*
		* @return Pixel - information of the pixel
		*/
		virtual const Pixel getPixel(S16 x,S16 y) = 0;

		/**
		*
		* Returns a pixel of the graphic.
		*
		* @param  position - Position object which holds the x and y coordinates of the pixel that shall be returned.
		*
		* @return Pixel - information of the pixel
		*/
		virtual const Pixel getPixel(const Position &position) = 0;
	
		/**
		*
		* Returns the alpha value of the graphic
		*
		* @return U8 - alpha value
		*/
		virtual U8 getAlpha() const = 0;

		/**
		* Cuts a rect out of the graphic.
		*
		* @param  position - Position object that holds the x and y coordinates on where to cut a rect out of the graphic.
		* @param  size - Size object that holds the width and height of the rect that shall get cut out of the graphic.
		*
		* @return GraphicPtr - New IGraphic implementation.
		*/
		virtual GraphicPtr cutRect(const Position &position,const Size &size) = 0;

		/**
		* Cuts a rect out of the graphic.
		*
		* @param  x - x coordinate on where to cut a rect out of the graphic.
		* @param  y - y coordinate on where to cut a rect out of the graphic.
		* @param  w - width of the rect that shall get cut out of the graphic.
		* @param  h - height of the rect that shall get cut out of the graphic.
		*
		* @return GraphicPtr - New IGraphic implementation.
		*/
		virtual GraphicPtr cutRect(U16 x,U16 y,U16 w,U16 h) = 0;
	
		/**
		*
		* Sets the graphic visibleness.
		*
		* @param  visible - bool that determines if graphic is visible or not
		*/
		virtual void setVisible(bool visible) = 0;
	
		/**
		*
		* graphic will get attached to the screen if this method is called.
		* That means that the graphic will stick on the screen.
		*/
		virtual void attachToScreen() = 0;
		
		/**
		*
		* graphic will get detached to the screen if this method is called
		* That means that the graphic will not stick on the screen.
		*/
		virtual void detachFromScreen() = 0;

		/**
		*
		* Returns if graphic is attached to the screen.
		*
		*
		* @return bool - true if the graphic is attached to the screen and false if not.
		*/
		virtual bool isScreenAttached() const = 0;
	
		/**
		*
		* Returns if graphic is visible.
		*
		* @return bool - true if the graphic is visible and false if not.
		*/
		virtual bool isVisible() const = 0;

		virtual bool drawAt(GraphicPtr graphic,const Position& position) = 0;

		virtual void setDrawOutOfBounds(bool val) = 0;

		virtual bool drawOutOfBounds() const = 0;

		virtual void setGraphicAsOrigin() = 0;
	
	protected:
	
		virtual bool _fitSize() = 0;

	};
}

#endif //__IGRAPHIC__