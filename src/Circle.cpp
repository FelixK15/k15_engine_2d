#include "Circle.h"

using namespace K15_Engine;

Circle::Circle()
{
	m_radius = 0;
}

Circle::Circle(S16 radius)
{
	m_radius = radius;
	_setSize();
}

Circle::~Circle()
{

}
 
const U32 Circle::getRadius() const
{
	return m_radius;
}

void Circle::setRadius( S16 radius )
{
	m_radius = radius;
	_setSize();
}

void Circle::_setSize()
{
	m_size = Size(m_radius * 2,m_radius * 2);
}