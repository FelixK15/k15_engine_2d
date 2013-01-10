#pragma once

#ifndef __ELLIPSE__
#define __ELLIPSE__

#include "StandardIncludes.h"
#include "Position.h"
#include "BaseShape.h"

namespace K15_Engine
{
	class K15ENGINE_API Ellipse
		: public BaseShape
	{
	public:

		Ellipse(U16 xr,U16 yr);

		~Ellipse();

		void setXRadius(U16 xr);

		void setYRadius(U16 yr);

		U16 getYRadius() const;

		U16 getXRadius() const;

	private:

		U16 m_xr,m_yr;

	};
}

#endif //__ELLIPSE__