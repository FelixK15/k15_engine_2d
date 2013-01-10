#include "Size.h"

using namespace K15_Engine;

Size::Size()
{
	m_width = 0;
	m_height = 0;
}

Size::Size(int width,int height)
{
	m_width = width;
	m_height = height;
}

void Size::setWidth(int width)
{
	m_width = width;
}

void Size::setHeight(int height)
{
	m_height = height;
}

int Size::getWidth() const
{
	return m_width;
}

int Size::getHeight() const
{
	return m_height;
}

Size & Size::operator=( const Size &otherSize )
{
	this->m_height = otherSize.m_height;
	this->m_width = otherSize.m_width;

	return *this;
}

Size & K15_Engine::Size::operator+( const Size &otherSize )
{
	this->m_height += otherSize.m_height;
	this->m_width += otherSize.m_width;

	return *this;
}

Size & K15_Engine::Size::operator-( const Size &otherSize )
{
	this->m_height -= otherSize.m_height;
	this->m_width -= otherSize.m_width;

	return *this;
}

bool Size::operator==( const Size &otherSize )
{
	return (this->m_height == otherSize.m_height && this->m_width == otherSize.m_width);
}

bool K15_Engine::Size::operator!=( const Size &otherSize )
{
	return !this->operator==(otherSize);
}
