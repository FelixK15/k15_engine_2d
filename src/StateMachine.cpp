#include "StateMachine.h"
#include "IState.h"

using namespace K15_Engine;

StateMachine::StateMachine()
{
//	m_curState = NULL;
	m_nextState = NULL;
	m_deleteCurState = false;
}

void StateMachine::setNextState( IState *nextState )
{
	if(m_nextState != NULL)
	{
		delete m_nextState;
		m_nextState = NULL;
	}
	m_nextState = nextState;
}

void StateMachine::update(U32 deltaTime)
{
	_checkForNextState();

	IState *curState = m_stateStack.top();
	if(curState != NULL){
		curState->update(deltaTime);
	}
}

StateMachine::~StateMachine()
{
// 	if(m_curState){
// 		delete m_curState;
// 		m_curState = NULL;
// 	}

	while(m_stateStack.size() > 0){
		removeCurState();
	}

	if(m_nextState){
		delete m_nextState;
		m_nextState = NULL;
	}
}

//Private Functions

void StateMachine::_checkForNextState()
{
	if(m_deleteCurState){
		m_stateStack.top()->end();
		delete m_stateStack.top();
		m_stateStack.pop();
		m_deleteCurState = false;
	}

	if(m_nextState != NULL){
// 		IState *oldState = m_curState;
// 
// 		if(oldState != NULL){
// 			oldState->end();
// 		}
// 
// 		m_curState = m_nextState;
// 		m_nextState = NULL;
		m_stateStack.push(m_nextState);
		m_nextState->start();
		m_nextState = NULL;
// 		delete oldState;
// 		oldState = NULL;
	}
}


void StateMachine::removeCurState()
{
	m_deleteCurState = true;

/*	IState *curState = m_stateStack.top();
	if(curState != NULL){
		curState->end();
		delete curState;

		m_stateStack.pop();
	}*/
}
