#pragma once

#ifndef __EVENTMANAGER__
#define __EVENTMANAGER__

#include "Singleton.h"
#include "Event.h"
#include "IEventListener.h"

namespace K15_Engine
{
	
	#define ADD_NEW_EVENT_TO_EVENTQUEUE() if(EventManager::getInstance() != NULL){ \
												EventManager::getInstance()->addEventToQueue(newEvent); \
											}
	
	#define EXECUTE_NEW_EVENT_IMMEDIATELY() if(EventManager::getInstance() != NULL){ \
												EventManager::getInstance()->triggerEvent(newEvent); \
											}
	
	#define NEW_EVENT(eventType) Event newEvent(eventType); 
	
	#define NEW_EVENT_WITH_1_ARG(eventType,arg1Name,arg1Value) NEW_EVENT(eventType) \
		newEvent.setArgument(String(arg1Name),Variant(arg1Value));
	
	#define NEW_EVENT_WITH_2_ARG(eventType,arg1Name,arg1Value,arg2Name,arg2Value) NEW_EVENT_WITH_1_ARG(eventType,arg1Name,arg1Value) \
		newEvent.setArgument(String(arg2Name),Variant(arg2Value));
	
	#define NEW_EVENT_WITH_3_ARG(eventType,arg1Name,arg1Value,arg2Name,arg2Value,arg3Name,arg3Value) NEW_EVENT_WITH_2_ARG(eventType,arg1Name,arg1Value,arg2Name,arg2Value) \
		newEvent.setArgument(String(arg3Name),Variant(arg3Value));
	
	#define NEW_EVENT_WITH_4_ARG(eventType,arg1Name,arg1Value,arg2Name,arg2Value,arg3Name,arg3Value,arg4Name,arg4Value) NEW_EVENT_WITH_3_ARG(eventType,arg1Name,arg1Value,arg2Name,arg2Value,arg3Name,arg3Value) \
		newEvent.setArgument(String(arg4Name),Variant(arg4Value));
	
	#define ADD_LISTENER(listener,type) EventManager::getInstance()->addListener(listener,type)
	
	#define REMOVE_LISTENER(listener,type) EventManager::getInstance()->removeListener(listener,type)
	
	typedef std::set<IEventListener*> EventListenerList;
	typedef std::map<EventType,EventListenerList> EventListenerMap;
	typedef std::list<Event> EventQueue;
	typedef std::set<Event> EventsInQueue;
	
	class K15ENGINE_API EventManager :
		public Singleton<EventManager>
	{
	public:
	
		EventManager();
	
		~EventManager();
	
		void update();
	
		bool init();
	
		String getName();
	
		void shutDown();
		/** BLUBLUB
		  * @param listener
		  * @param eventType
		  * @returns bool
		  */
		bool addListener(IEventListener *listener,const EventType &eventType);
	
		bool removeListener(IEventListener *listener,const EventType &eventType);
	
		bool triggerEvent(Event &gameEvent);
	
		bool addEventToQueue(const Event &gameEvent);
	
		bool removeEventFromQueue(Event &gameEvent);
	
		static EventManager *getInstance();
	
	private:
	
		bool _verifyEventType(const EventType &gameEvent);
	
		EventListenerMap m_eventListenerMap;
	
		EventQueue m_eventQueue;
	
		EventsInQueue m_eventsInQueue;
	
	};
}
#endif //__EVENTMANAGER__