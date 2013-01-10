#pragma once

#ifndef __KLINE__
#define __KLINE__

#include "StandardIncludes.h"
#include "Position.h"

namespace K15_Engine
{
	class K15ENGINE_API Line
	{

	public:

		Line(Position pos1,Position pos2,U8 thickness = 2);

		Line(S16 x,S16 y,S16 x2,S16 y2,U8 thickness = 2);

		~Line();

		Position getPos1() const;

		Position getPos2() const;

		U8 getThickness() const;

		void setPos1(S16 x,S16 y);

		void setPos1(Position pos1);

		void setPos2(S16 x,S16 y);

		void setPos2(Position pos2);

		void setThickness(U8 thickness);

	private:
		U8 m_thickness;

		Position m_pos1;

		Position m_pos2;
	};
}

#endif //__KLINE__