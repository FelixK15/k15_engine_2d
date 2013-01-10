///////////////////////////////////////////////////////////
//  Rectangle.cpp
//  Implementation of the Class Rectangle
//  Created on:      16-Aug-2011 21:00:02
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#include "Rectangle.h"

using namespace K15_Engine;

Rectangle::Rectangle()
{

}

Rectangle::Rectangle( const Size &size )
{
	m_size = size;
}

Rectangle::Rectangle( U16 w,U16 h )
{
	m_size = Size(w,h);
}

Rectangle::~Rectangle()
{

}

Rectangle & Rectangle::operator=( const Rectangle &otherRect )
{
	this->m_size = otherRect.m_size;

	return *this;
}

Rectangle & Rectangle::operator+( const Rectangle &otherRect )
{
	this->m_size = this->m_size + otherRect.m_size;

	return *this;
}

Rectangle & Rectangle::operator-( const Rectangle &otherRect )
{

	this->m_size = this->m_size - otherRect.m_size;

	return *this;
}

bool Rectangle::operator==( const Rectangle &otherRect )
{
	return this->m_size == otherRect.m_size;
}

bool Rectangle::operator!=( const Rectangle &otherRect )
{
	return !this->operator==(otherRect);
}