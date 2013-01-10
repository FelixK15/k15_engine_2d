#include "EventListenerComponent.h"
#include "EventManager.h"

using namespace K15_Engine;

EventListenerComponent::EventListenerComponent(EventType eventType)
	: AbstractComponent("EventListenerComponent"),
	m_type(eventType)
{
	ADD_LISTENER(this,eventType);
}

EventListenerComponent::~EventListenerComponent()
{
	REMOVE_LISTENER(this,m_type);
}

bool EventListenerComponent::handleMessage( Event const & componentEvent )
{
	return true;
}

bool EventListenerComponent::handleEvent(Event const &gameEvent)
{
	if(gameEvent.getType() == m_type){
		m_parent->broadcastMessage(gameEvent);
		return true;
	}

	return false;
}

AbstractComponent * EventListenerComponent::clone()
{
	EventListenerComponent *retComponent = new EventListenerComponent(m_type);
	return static_cast<AbstractComponent*>(retComponent);
}
