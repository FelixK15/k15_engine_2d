#pragma once

#ifndef __IGAME__
#define __IGAME__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class StateMachine;
	
	class K15ENGINE_API IGame
	{
	public:

		virtual void start() = 0;
	
		virtual void update() = 0;
	
		virtual void quit() = 0;
	
		virtual bool isRunning() = 0;
	};
}

#endif //__IGAME__