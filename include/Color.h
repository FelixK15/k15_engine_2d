#pragma once

#ifndef __COLOR__
#define __COLOR__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API Color
	{
	public:
		Color();

		Color(U8 r,U8 g,U8 b);

		Color(U8 r,U8 g,U8 b,U8 a);

		Color(const Color &otherColor);

		~Color();

		void setR(U8 r);

		void setG(U8 g);

		void setB(U8 b);

		void setA(U8 a);

		bool isEmpty() const;

		U8 getR() const;

		U8 getG() const;

		U8 getB() const;

		U8 getA() const;

		U32 toInt() const;

		Color &operator=(const Color &otherColor);

		Color &operator+(const Color &otherColor);

		Color &operator-(const Color &otherColor);

		bool operator==(const Color &otherColor) const;

		bool operator!=(const Color &otherColor) const;

		static Color toColor(int color);

		//PREDEFINED COLORS
		static Color Red;

		static Color Green;

		static Color Blue;

		static Color Yellow;

		static Color White;

		static Color Black;

		static Color EmptyColor;

		static Color Transparent;

	private:
		Color(bool empty);

		void _copy(const Color &otherColor);

		U8 r,g,b,a; //32bit

		bool m_empty; //8bit

		U8 pad[3]; //24bit;
	};
}
#endif //__COLOR__
