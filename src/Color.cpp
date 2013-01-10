#include "Color.h"

using namespace K15_Engine;

Color Color::Red = Color(255,0,0);
Color Color::Green = Color(0,255,0);
Color Color::Blue = Color(0,0,255);
Color Color::Yellow = Color(255,255,0);
Color Color::White = Color(255,255,255);
Color Color::Black = Color(0,0,0);
Color Color::EmptyColor = Color(true);
Color Color::Transparent = Color(0,0,0,0);

Color::Color()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
	this->m_empty = false;
}

Color::Color(U8 r,U8 g,U8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
	this->m_empty = false;
}

Color::Color(U8 r,U8 g,U8 b,U8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->m_empty = false;
}

Color::Color(bool empty)
{
	this->m_empty = true;
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

Color::~Color()
{

}

void Color::setR( U8 r )
{
	this->r = r;
}

void Color::setG( U8 g )
{
	this->g = g;
}

void Color::setB( U8 b )
{
	this->b = b;
}

void Color::setA( U8 a )
{
	this->a = a;
}

bool Color::isEmpty() const
{
	return m_empty;
}

U8 Color::getR() const
{
	return r;
}

U8 Color::getG() const
{
	return g;
}

U8 Color::getB() const
{
	return b;
}

U8 Color::getA() const
{
	return a;
}

U32 Color::toInt() const
{
	return m_empty ? 0 : (((((r << 8) + g) << 8) + b << 8) + a);
}

Color &Color::operator=( const Color &otherColor )
{
	this->_copy(otherColor);

	return *this;
}

Color & Color::operator+( const Color &otherColor )
{
	if(this->a + otherColor.a <= 255){
		this->a += otherColor.a;
	}

	if(this->r + otherColor.r <= 255){
		this->r += otherColor.r;
	}
	if(this->g + otherColor.g <= 255){
		this->g += otherColor.g;
	}
	if(this->b + otherColor.b <= 255){
		this->b += otherColor.b;
	}

	return *this;
}

Color & Color::operator-( const Color &otherColor )
{
	if(this->a - otherColor.a >= 0){
		this->a -= otherColor.a;
	}

	if(this->r - otherColor.r >= 0){
		this->r -= otherColor.r;
	}
	if(this->g - otherColor.g >= 0){
		this->g -= otherColor.g;
	}
	if(this->b - otherColor.b >= 0){
		this->b -= otherColor.b;
	}

	return *this;
}

bool Color::operator==( const Color &otherColor ) const
{
	return (this->a == otherColor.a && this->r == otherColor.r && this->g == otherColor.g && this->b == otherColor.b && this->m_empty == otherColor.m_empty);
}

bool Color::operator!=( const Color &otherColor ) const
{
	return !(this->a == otherColor.a && this->r == otherColor.r && this->g == otherColor.g && this->b == otherColor.b && this->m_empty == otherColor.m_empty);
}

Color K15_Engine::Color::toColor( int color )
{
	U8 colorArr[4];
	colorArr[3] = (color >> 24) & 0xFF;
	colorArr[2] = (color >> 16) & 0xFF;
	colorArr[1] = (color >> 8) & 0xFF;
	colorArr[0] = color & 0xFF;
	return Color(colorArr[0],colorArr[1],colorArr[2],colorArr[3]);
}

Color::Color( const Color &otherColor )
{
	this->_copy(otherColor);
}

void Color::_copy( const Color &otherColor )
{
	this->a = otherColor.a;
	this->r = otherColor.r;
	this->g = otherColor.g;
	this->b = otherColor.b;
	this->m_empty = otherColor.m_empty;
}
