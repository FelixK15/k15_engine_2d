#pragma once

#ifndef __VERSATILECOMPONENT__
#define __VERSATILECOMPONENT__

#include "StandardIncludes.h"
#include "AbstractComponent.h"

namespace K15_Engine
{
	typedef std::function<bool(const Event,GameObject*)> HandleMessageFunction;
	typedef std::function<void(U32,GameObject*)> UpdateFunction;
	typedef std::function<void(GameObject*)> StartFunction;
	typedef StartFunction ShutdownFunction;
	class K15ENGINE_API VersatileComponent
		: public AbstractComponent
	{

	public:
		VersatileComponent(String type,HandleMessageFunction handleEventFunction,UpdateFunction updateFunction);

		VersatileComponent(String type,StartFunction startFunction,HandleMessageFunction handleEventFunction,UpdateFunction updateFunction);

		VersatileComponent(String type,StartFunction startFunction,ShutdownFunction shutdownFunction,HandleMessageFunction handleEventFunction,UpdateFunction updateFunction);

		VersatileComponent(const VersatileComponent &vComponent);

		~VersatileComponent();

		GameObject *getParent();

		void start();

		void update(U32 gameTime);

		bool handleMessage(Event const & componentEvent);

		AbstractComponent *clone();

		void shutdown();

	private:
		StartFunction m_startFunction;
		UpdateFunction m_updateFunction;
		HandleMessageFunction m_handleMessageFunction;
		ShutdownFunction m_shutdownFunction;
	};
}

#endif //__VERSATILECOMPONENT__