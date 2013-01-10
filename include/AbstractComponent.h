#pragma once
#ifndef __BASECOMPONENT__
#define __BASECOMPONENT__

#include "GameObject.h"
#include "Size.h"
#include "Position.h"

namespace K15_Engine
{
	class K15ENGINE_API AbstractComponent
	{

	friend class GameObject;

	public:
		AbstractComponent(const String &type)
			: m_type(type){}

		virtual ~AbstractComponent(){}

		const String &getType() const {return m_type;}

		bool isDebugMode(){return m_debug;}

		void setParent(GameObject *parent){m_parent = parent;}

		GameObject* getParent(){return m_parent;}

		virtual AbstractComponent *clone() = 0;

		virtual void setDebugMode(bool val){m_debug = val;}

		virtual bool handleMessage(const Event &gameEvent ) = 0;

		virtual void start(){}

		virtual void setSize(const Size& size){}

		virtual void setPosition(const Position& position){}

		virtual void setAngle(S16 angle){}

		virtual void shutdown(){}

		virtual void update(U32 gameTime){}

	protected:

		GameObject *m_parent;

		const String m_type;

		bool m_debug;
	};
}

#endif //__COMPONENT__