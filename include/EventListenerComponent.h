#pragma once

#ifndef __EVENTLISTENERCOMPONENT__
#define __EVENTLISTENERCOMPONENT__

#include "IEventListener.h"
#include "AbstractComponent.h"

namespace K15_Engine
{
	class K15ENGINE_API EventListenerComponent
		: public IEventListener,
		  public AbstractComponent
	{
	public:

		EventListenerComponent(EventType eventType);

		~EventListenerComponent();

		bool handleMessage(Event const & componentEvent);

		bool handleEvent(Event const &gameEvent);

		AbstractComponent *clone();

	private:

		EventType m_type;

	};
}

#endif //__CLASSNAME__