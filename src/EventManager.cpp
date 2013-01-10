#include "EventManager.h"

using namespace K15_Engine;

template<> EventManager* Singleton<EventManager>::m_instance = 0;

EventManager::EventManager()
{

}

EventManager::~EventManager()
{
	m_eventListenerMap.clear();
	m_eventQueue.clear();
	m_eventsInQueue.clear();
}

void EventManager::update()
{
	while(m_eventQueue.size() > 0){
		Event curEvent = m_eventQueue.back();
		triggerEvent(curEvent);
		m_eventsInQueue.erase(m_eventsInQueue.find(curEvent));
		m_eventQueue.pop_back();
	}
}

bool EventManager::init()
{
	return true;
}

String EventManager::getName()
{
	return "EventManager";
}

void EventManager::shutDown()
{

}

bool EventManager::addListener(IEventListener *listener,const EventType &eventType )
{
	if(!_verifyEventType(eventType))
		return false;

	if(m_eventListenerMap[eventType].find(listener) == m_eventListenerMap[eventType].end())
	{
		m_eventListenerMap[eventType].insert(listener);
		return true;
	}
	
	return false;
}

bool EventManager::removeListener(IEventListener *listener,const EventType &eventType )
{
	if(m_eventListenerMap[eventType].find(listener) == m_eventListenerMap[eventType].end()){
		return false;
	}

	m_eventListenerMap[eventType].erase(listener);
	return true;
}

bool EventManager::triggerEvent(Event &gameEvent)
{
	if(m_eventListenerMap[gameEvent.getType()].size() <= 0){
		return false;
	}

	for(EventListenerList::iterator i = m_eventListenerMap[gameEvent.getType()].begin();
		i != m_eventListenerMap[gameEvent.getType()].end();++i){
		
		(*i)->handleEvent(gameEvent);
	}

	return true;
}

bool EventManager::addEventToQueue(const Event &gameEvent)
{
	if(m_eventsInQueue.find(gameEvent) == m_eventsInQueue.end()){
		m_eventQueue.push_front(gameEvent);
		m_eventsInQueue.insert(gameEvent);
		return true;
	}

	return false;
}

bool EventManager::removeEventFromQueue(Event &gameEvent)
{
	if(m_eventsInQueue.find(gameEvent) == m_eventsInQueue.end()){
		return false;
	}

	m_eventQueue.remove(gameEvent);
	m_eventsInQueue.erase(m_eventsInQueue.find(gameEvent));

	return true;
}

bool EventManager::_verifyEventType( const EventType &gameEvent)
{
	if(gameEvent.getIdentifier() > 0)
		return true;

	return false;
}

EventManager * EventManager::getInstance()
{
	return m_instance;
}
