#pragma once

#ifndef __ABSTRACTSHAPE__
#define __ISH__ABSTRACTSHAPE__APE__

#include "StandardIncludes.h"
#include "Position.h"
#include "Size.h"

namespace K15_Engine
{
	class K15ENGINE_API BaseShape
	{

	public:

		Size getSize();

		const Size& getSize() const;

		void setSize(const Size &size);

		void setSize(U16 w,U16 h);

	protected:

		Size m_size;
	};
}

#endif //__ABSTRACTSHAPE__