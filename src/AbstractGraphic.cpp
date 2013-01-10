#include "AbstractGraphic.h"
#include "Log.h"
using namespace K15_Engine;

AbstractGraphic::AbstractGraphic()
{
	m_screenAttached = false;
	m_visible = true;
	m_locked = false;
	m_outOfBounds = false;
}

AbstractGraphic::~AbstractGraphic()
{

}

bool AbstractGraphic::isLocked() const
{
	return m_locked;
}

void AbstractGraphic::setPosition( S16 x,S16 y )
{
	m_position.setX(x);
	m_position.setY(y);
}

void AbstractGraphic::setSize( U16 w,U16 h )
{
	m_size.setHeight(h);
	m_size.setWidth(w);
}

void AbstractGraphic::getSize( U16 *w,U16 *h ) const
{
	if(w)
		*w = m_size.getWidth();

	if(h)
		*h = m_size.getHeight();
}

void AbstractGraphic::getPosition( S16 *x,S16 *y ) const
{
	if(x)
		*x = m_position.getX();

	if(y)
		*y = m_position.getY();
}

void AbstractGraphic::setVisible( bool visible )
{
	m_visible = visible;
}

void AbstractGraphic::attachToScreen()
{
	m_screenAttached = true;
}

void AbstractGraphic::detachFromScreen()
{
	m_screenAttached = false;
}

bool AbstractGraphic::isScreenAttached() const
{
	return m_screenAttached;
}

bool AbstractGraphic::isVisible() const
{
	return m_visible;
}

U8 AbstractGraphic::getAlpha() const
{
	return m_alphaValue;
}

bool AbstractGraphic::fillWithColor( U8 r,U8 g,U8 b,U8 a )
{
	return fillWithColor(Color(r,g,b,a));
}

bool AbstractGraphic::setColorkey( U8 r,U8 g,U8 b )
{
	return setColorkey(Color(r,g,b));
}

void AbstractGraphic::setPosition( const Position &position )
{
	m_position = position;
}

void AbstractGraphic::setSize( const Size &size )
{
	m_size = size;
}

const Size AbstractGraphic::getSize() const
{
	return m_size;
}

const Position AbstractGraphic::getPosition() const
{
	return m_position;
}

bool AbstractGraphic::setPixel( S16 x,S16 y,const Pixel &color )
{
	return setPixel(Position(x,y),color);
}

bool AbstractGraphic::setPixel( S16 x,S16 y,U8 r,U8 g,U8 b, U8 a)
{
	return setPixel(Position(x,y),Color(r,g,b,a));
}

const Pixel AbstractGraphic::getPixel( S16 x,S16 y )
{
	return getPixel(Position(x,y));
}

GraphicPtr AbstractGraphic::cutRect( U16 x,U16 y,U16 w,U16 h )
{
	return cutRect(Position(x,y),Size(w,h));
}