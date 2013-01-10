#pragma once

#ifndef __SIZE__
#define __SIZE__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API Size
	{
	public:
		
		Size();
	
		Size(int width,int height);
		
		void setWidth(int width);
	
		void setHeight(int height);

		int getWidth() const;
	
		int getHeight() const;

		Size &operator=(const Size &otherSize);

		Size &operator+(const Size &otherSize);

		Size &operator-(const Size &otherSize);

		bool operator==(const Size &otherSize);

		bool operator!=(const Size &otherSize);
	
	private:
		int m_width,m_height; // 64 bits;
	};
}

#endif //__SIZE__