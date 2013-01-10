#include "Line.h"

using namespace K15_Engine;

Line::Line(S16 x,S16 y,S16 x2,S16 y2,U8 thickness)
{
	m_pos1 = Position(x,y);
	m_pos2 = Position(x2,y2);
	m_thickness = thickness < 2 ? 2 : thickness;
}

Line::Line(Position pos1,Position pos2,U8 thickness)
{
	m_pos1 = pos1;
	m_pos2 = pos2;
	m_thickness = thickness < 2 ? 2 : thickness;
}

Line::~Line()
{

}

Position Line::getPos1() const
{
	return m_pos1;
}

Position Line::getPos2() const
{
	return m_pos2;
}

U8 Line::getThickness() const
{
	return m_thickness;
}

void Line::setPos1( S16 x,S16 y )
{
	setPos1(Position(x,y));
}

void Line::setPos1( Position pos1 )
{
	m_pos1 = pos1;
}

void Line::setPos2( S16 x,S16 y )
{
	setPos2(Position(x,y));
}

void Line::setPos2( Position pos2 )
{
	m_pos2 = pos2;
}

void Line::setThickness( U8 thickness )
{
	m_thickness = thickness;
}
