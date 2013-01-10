#include "SDL_MessageQueue.h"
#include "Events.h"
#include "Log.h"
#include "EventManager.h"

using namespace K15_Engine;

SDL_MessageQueue::SDL_MessageQueue()
{
	WRITE_DEBUG("SDL_InputManager created.");
}

SDL_MessageQueue::~SDL_MessageQueue()
{
	WRITE_DEBUG("SDL_InputManager destroyed.");
}

bool SDL_MessageQueue::hasNextMessage()
{
	return SDL_PollEvent(&m_curEvent) != 0;
}

void SDL_MessageQueue::processCurrentMessage()
{
	if(m_curEvent.type == SDL_KEYDOWN || m_curEvent.type == SDL_KEYUP){
		_processKeyboardInput();
	}else if(m_curEvent.type == SDL_MOUSEMOTION){
		_processMouseMovement();
	}else if(m_curEvent.type == SDL_MOUSEBUTTONUP || m_curEvent.type == SDL_MOUSEBUTTONDOWN){
		_processMouseInput();
	}else if(m_curEvent.type == SDL_QUIT || m_curEvent.type == SDL_VIDEORESIZE || m_curEvent.type == SDL_APPMOUSEFOCUS){
		_processWindowInput();
	}
}

void SDL_MessageQueue::_processKeyboardInput()
{
	if(m_curEvent.type == SDL_KEYDOWN){

		if(m_curEvent.key.keysym.sym != SDLK_RETURN && m_curEvent.key.keysym.sym != SDLK_BACKSPACE){
			if(m_curEvent.key.keysym.unicode != 0){
				NEW_EVENT_WITH_1_ARG(Events::UnicodeKeyboardPressed,"key",m_curEvent.key.keysym.unicode);
				ADD_NEW_EVENT_TO_EVENTQUEUE();
			}
		}
		
		NEW_EVENT_WITH_1_ARG(Events::KeyboardPressed,"key",m_curEvent.key.keysym.sym);
		ADD_NEW_EVENT_TO_EVENTQUEUE();
		
	}else if(m_curEvent.type == SDL_KEYUP){
		NEW_EVENT_WITH_1_ARG(Events::KeyboardReleased,"key",m_curEvent.key.keysym.sym);
		ADD_NEW_EVENT_TO_EVENTQUEUE();
 	}

	
}

void SDL_MessageQueue::_processMouseInput()
{
	if(m_curEvent.type == SDL_MOUSEBUTTONDOWN){
		NEW_EVENT_WITH_1_ARG(Events::MousePressed,"button",m_curEvent.button.button);
		ADD_NEW_EVENT_TO_EVENTQUEUE();
	}else if(m_curEvent.type == SDL_MOUSEBUTTONUP){
		NEW_EVENT_WITH_1_ARG(Events::MouseReleased,"button",m_curEvent.button.button);
		ADD_NEW_EVENT_TO_EVENTQUEUE();
	}
}

void SDL_MessageQueue::_processMouseMovement()
{
	NEW_EVENT_WITH_2_ARG(Events::MouseMoved,"x",m_curEvent.motion.x,"y",m_curEvent.motion.y);
		EXECUTE_NEW_EVENT_IMMEDIATELY();
		ADD_NEW_EVENT_TO_EVENTQUEUE();
}

void SDL_MessageQueue::_processWindowInput()
{
	if(m_curEvent.type == SDL_APPMOUSEFOCUS){
		if(m_curEvent.active.gain == 1){
			NEW_EVENT(Events::FocusGained);
			ADD_NEW_EVENT_TO_EVENTQUEUE();
		}else if(m_curEvent.active.gain == 0){
			NEW_EVENT(Events::FocusLost);
			ADD_NEW_EVENT_TO_EVENTQUEUE();
		}
	}else if(m_curEvent.type == SDL_QUIT){
		NEW_EVENT(Events::WindowClosed);
		ADD_NEW_EVENT_TO_EVENTQUEUE();
	}
}