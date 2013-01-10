#include "Position.h"

using namespace K15_Engine;

Position::Position()
{
	m_x = 0;
	m_y = 0;
}

Position::Position(int x,int y)
{
	m_x = x;
	m_y = y;
}

void Position::setX(int x)
{
	m_x = x;
}

void Position::setY(int y)
{
	m_y = y;
}

int Position::getX() const
{
	return m_x;
}

int Position::getY() const
{
	return m_y;
}

Position &Position::operator=(const Position &otherPosition)
{
	this->m_x = otherPosition.m_x;
	this->m_y = otherPosition.m_y;

	return *this;
}

Position & Position::operator+( const Position &otherPosition )
{
	this->m_x += otherPosition.m_x;
	this->m_y += otherPosition.m_y;

	return *this;
}

Position & Position::operator-( const Position &otherPosition )
{
	this->m_x -= otherPosition.m_x;
	this->m_y -= otherPosition.m_y;

	return *this;
}

bool Position::operator==(const Position &otherPosition)
{
	return (this->m_x == otherPosition.m_x && this->m_y == otherPosition.m_y);
}

bool Position::operator!=( const Position &otherPosition )
{
	return !this->operator==(otherPosition);
}
