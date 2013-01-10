#pragma once

#ifndef __ISTATE__
#define __ISTATE__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API IState
	{
	public:
	
		virtual bool start() = 0;
	
		virtual void update(U32 deltaTime) = 0;
	
		virtual void end() = 0;
	};
}

#endif //__ISTATE__