#pragma once

#ifndef __IEVENTLISTENER__
#define __IEVENTLISTENER__

#include "DLL_Header.h"
#include "Event.h"

namespace K15_Engine
{
	class K15ENGINE_API IEventListener
	{
	public:
		
		virtual bool handleEvent(Event const &gameEvent) = 0
		{
			return true;
		}
	};
}

#endif //__IEVENTLISTENER__