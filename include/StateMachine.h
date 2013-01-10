#pragma once

#ifndef __STATEMACHINE__
#define __STATEMACHINE__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class IState;
	
	typedef	std::stack<IState*> StateStack;
	class K15ENGINE_API StateMachine
	{
	public:
	
		StateMachine();
	
		void setNextState(IState *nextState);
	
		void update(U32 deltaTime);

		void removeCurState();
	
		~StateMachine();
	
	private:
		void _checkForNextState();
	

		bool m_deleteCurState;
		StateStack m_stateStack;
		IState *m_nextState;
	};
}
#endif //__STATEMACHINE__