#pragma once

#ifndef __ABSTRACTGRAPHIC__
#define __ABSTRACTGRAPHIC__

#include "IGraphic.h"

namespace K15_Engine
{
	class K15ENGINE_API AbstractGraphic : public IGraphic
	{
	public:
		AbstractGraphic();
	
		virtual ~AbstractGraphic();
	
		virtual bool setColorkey( U8 r,U8 g,U8 b );

		virtual bool isLocked() const;

		virtual U8 getAlpha() const;

		virtual void setPosition( const Position &position );

		virtual void setPosition(S16 x,S16 y);

		virtual void setSize( const Size &size );

		virtual void setSize(U16 w,U16 h);

		virtual void setVisible(bool visible);

		virtual void attachToScreen();

		virtual void detachFromScreen();

		virtual bool isScreenAttached() const;

		virtual bool isVisible() const;

		virtual const Size getSize() const;

		virtual void getSize(U16 *w,U16 *h) const;

		virtual const Position getPosition() const;

		virtual void getPosition(S16 *x,S16 *y) const;

		virtual bool setPixel(S16 x,S16 y,const Pixel &pixel);

		virtual bool setPixel(S16 x,S16 y,U8 r,U8 g,U8 b,U8 a);

		virtual bool fillWithColor( U8 r,U8 g,U8 b,U8 a );

		virtual const Pixel getPixel( S16 x,S16 y );

		virtual GraphicPtr cutRect( U16 x,U16 y,U16 w,U16 h );

		virtual bool fillWithColor(const Color &color) = 0;

		virtual bool setColorkey(const Color &colorkey) = 0;

		virtual bool setPixel(const Position &position,const Pixel &pixel) = 0;

		virtual const Pixel getPixel(const Position &position) = 0;

		virtual GraphicPtr cutRect(const Position &position,const Size &size ) = 0;

		virtual void setDrawOutOfBounds(bool val){m_outOfBounds = true;}

		virtual bool drawOutOfBounds() const {return m_outOfBounds;}


	protected:

		/*virtual bool _fitSize() = 0;*/

		Position m_position;

		Size m_size;

		Color m_colorkey;

		bool m_screenAttached;

		bool m_visible;

		bool m_hasColorkey;

		bool m_locked;

		bool m_outOfBounds;

		U8 m_alphaValue;

	};
}

#endif //__ABSTRACTGRAPHIC__