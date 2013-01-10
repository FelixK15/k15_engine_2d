#pragma once

#ifndef __CIRCLE__
#define __CIRCLE__

#include "StandardIncludes.h"
#include "Position.h"
#include "BaseShape.h"

namespace K15_Engine
{
	class K15ENGINE_API Circle
		: public BaseShape
	{
	public:
		Circle();

		Circle(S16 radius);

		~Circle();

		const U32 getRadius() const;

		void setRadius(S16 radius);

	private:

		void _setSize();

		S16 m_radius;

	};
}
#endif // __Circle__
