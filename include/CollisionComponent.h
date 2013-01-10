#pragma once

#ifndef __COLLISIONCOMPONENT__
#define __COLLISIONCOMPONENT__

#include "AbstractComponent.h"

namespace K15_Engine
{
	class K15ENGINE_API CollisionComponent : public AbstractComponent
	{
	public:

		CollisionComponent();

		CollisionComponent(const CollisionComponent& component);

		virtual ~CollisionComponent();

		virtual CollisionComponent *clone();

		virtual bool handleMessage(const Event &gameEvent );

		virtual void update(U32 gameTime);

		virtual void setSize(const Size& size);

		virtual void setPosition(const Position& position);

		void setHitBoxSize(const Size& size){m_hitBoxSize = size;}

		void setHitBoxPosition(const Position& position){m_hitBoxPosition = position;}

		const Size& getHitBoxSize() const {return m_hitBoxSize;}

		const Position& getHitBoxPosition() const {return m_hitBoxPosition;}

		void setHitBoxAngle(S16 angle);

		void setActive(bool val){m_active = val;}

		bool isActive(){return m_active;}

		void setCollided(bool val){m_collided = val;}

		bool isCollided(){return m_collided;}

	private:

		Size m_hitBoxSize;

		Position m_hitBoxPosition;

		bool m_active, m_collided;
	};
}

#endif