#pragma once

#ifndef __POSITION__
#define __POSITION__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API Position
	{
	public:
	
		Position();
	
		Position(int x,int y);
	
		void setX(int x);
	
		void setY(int y);
	
		int getX() const;
	
		int getY() const;

		Position &operator=(const Position &otherPosition);

		Position &operator+(const Position &otherPosition);

		Position &operator-(const Position &otherPosition);

		bool operator==(const Position &otherPosition);

		bool operator!=(const Position &otherPosition);
	
	private:
		int m_x,m_y;
	};
}

#endif //__POSITION__