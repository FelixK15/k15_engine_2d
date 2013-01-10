#pragma once

#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "StateMachine.h"
#include "Size.h"
#include "Event.h"
#include "Position.h"

#include "StandardIncludes.h"

#define GET_COMPONENT(type) getComponent<type>(#type)

namespace K15_Engine
{
	class AbstractComponent;

	typedef HashedString ComponentType;
	typedef std::vector<AbstractComponent*> ComponentList;
	typedef ComponentList::iterator ComponentListIter;

	class K15ENGINE_API GameObject
	{
	public:
		
		GameObject();

		GameObject(const String &type);

		GameObject(const GameObject&);
	
		~GameObject();
	
		int getID() const{return m_gameObjectID;}
	
		const String& getType() const{return m_type;}
	
		void setType(const String &type){m_type = type;}
	
		void setNextState(IState *nextState);

		void setPosition(const Position& position);
		
		void setPosition(S16 x,S16 y){setPosition(Position(x,y));}

		void setPositionNextTick(const Position& position){m_positionNextTick = position;}

		void setPositionNextTick(S16 x,S16 y){setPositionNextTick(Position(x,y));}

		void setSize(const Size& size);

		void setSize(S16 w,S16 h){setSize(Size(w,h));}

		void setSizeNextTick(const Size& size){m_sizeNextTick = size;}

		void setSizeNextTick(S16 w,S16 h){setSizeNextTick(Size(w,h));}

		void setAngle(S16 angle);

		void setAngleNextTick(S16 angle);

		void autoUpdate(bool);

		U16 getAngle() const {return m_angle;}

		Position getPosition() const {return m_position;}

		Size getSize() const {return m_size;}

		void restorePosition(){m_position = m_positionLastTick;}

		void restoreSize(){m_size = m_sizeLastTick;}

		void restoreAngle(){m_angle = m_angleLastTick;}

		bool addComponent(AbstractComponent *component);

		bool removeComponent(const String &type);

		void broadcastMessage(Event const & componentEvent);

		virtual bool update(U32 deltaTime);

		virtual void setDebugMode(bool var);
	
		GameObject &operator=(GameObject const &otherGameObject);

		template<class T>
		T *getComponent(const String &componentName)
		{
			if(m_components.size() > 0){
				for(ComponentList::iterator i = m_components.begin();i != m_components.end();i++){
					if((*i)->getType() == componentName){
						return static_cast<T*>((*i));
					}
				}
			}

			return NULL;
		}

		template<class T>
		std::list<T*> getComponents(const String &componentName)
		{
			std::list<T*> componentList;

			if(m_components.size() > 0){
				for(ComponentList::iterator i = m_components.begin();i != m_components;i++){
					if((*i)->getType() == componentName){
						componentList.push_back(static_cast<T*>((*i)));
					}
				}
			}

			return componentList;
		}

	private:

		void _preConstruct();

		void _saveOldPosition(){m_positionLastTick = m_position;}

		void _saveOldSize(){m_sizeLastTick = m_size;}

		void _saveOldAngle(){m_angleLastTick = m_angle;}

		const int m_gameObjectID;

		bool m_autoUpdate;

		String m_type;

		U32 m_lastUpdated;

	protected:

		virtual void preUpdate(){};

		virtual void postUpdate(){};

		StateMachine m_finiteStateMachine;
	
		ComponentList m_components;

		U16 m_angle, m_angleNextTick, m_angleLastTick;

		Size m_size, m_sizeNextTick, m_sizeLastTick;

		Position m_position, m_positionNextTick, m_positionLastTick;
	};
}

#endif //__GAMEOBJECT__
