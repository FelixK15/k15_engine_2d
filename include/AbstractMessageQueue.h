#pragma once

#ifndef __INPUTMANAGER__
#define __INPUTMANAGER__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API AbstractMessageQueue
	{
	public:

		virtual bool hasNextMessage() = 0;

		virtual void processCurrentMessage() = 0;
	};
}

#endif //__INPUTMANAGER__