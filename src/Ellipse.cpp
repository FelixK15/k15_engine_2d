#include "Ellipse.h"

using namespace K15_Engine;

Ellipse::Ellipse( U16 xr,U16 yr )
{
	m_xr = xr;
	m_yr = yr;
}

Ellipse::~Ellipse()
{

}

void Ellipse::setXRadius( U16 xr )
{
	m_xr = xr;
}

void Ellipse::setYRadius( U16 yr )
{
	m_yr = yr;
}

U16 Ellipse::getXRadius() const
{
	return m_xr;
}

U16 Ellipse::getYRadius() const
{
	return m_yr;
}