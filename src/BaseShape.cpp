#include "BaseShape.h"

using namespace K15_Engine;


Size BaseShape::getSize()
{
	return m_size;
}

const Size& BaseShape::getSize() const
{
	return m_size;
}

void BaseShape::setSize( const Size& size )
{
	m_size = size;
}

void BaseShape::setSize( U16 w,U16 h )
{
	setSize(Size(w,h));
}