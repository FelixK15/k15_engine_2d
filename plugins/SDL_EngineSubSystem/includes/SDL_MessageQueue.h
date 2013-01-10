#pragma once

#ifndef __SDL_MESSAGEQUEUESUBSYSTEM__
#define __SDL_MESSAGEQUEUESUBSYSTEM__

#include "StandardIncludes.h"
#include "AbstractMessageQueue.h"
#include "SDL\SDL_events.h"

namespace K15_Engine
{
	class SDL_MessageQueue : public AbstractMessageQueue
	{

	public:
		SDL_MessageQueue();

		virtual ~SDL_MessageQueue();

		virtual bool hasNextMessage();

		virtual void processCurrentMessage();

	private:
		void _processKeyboardInput();

		void _processMouseMovement();

		void _processMouseInput();

		void _processWindowInput();

		SDL_Event m_curEvent;
	};
}

#endif //__SDL_MESSAGEQUEUESUBSYSTEM__