#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "Size.h"
#include "Position.h"
#include "BaseShape.h"

namespace K15_Engine
{
	class K15ENGINE_API Rectangle
		: public BaseShape
	{

	public:
		Rectangle();

		Rectangle(const Size &size);

		Rectangle(U16 w,U16 h);

		~Rectangle();

		Rectangle &operator=(const Rectangle &otherRect);

		Rectangle &operator+(const Rectangle &otherRect);

		Rectangle &operator-(const Rectangle &otherRect);

		bool operator==(const Rectangle &otherRect);

		bool operator!=(const Rectangle &otherRect);

	};
}


#endif // __RECTANGLE__
