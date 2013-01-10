///////////////////////////////////////////////////////////
//  AnimatedComponent.h
//  Implementation of the Class AnimatedComponent
//  Created on:      17-Aug-2011 22:18:02
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#pragma once

#ifndef __ANIMATEDCOMPONENT__
#define __ANIMATEDCOMPONENT__

#include "AbstractComponent.h"
#include "Animation.h"

namespace K15_Engine
{
	typedef std::map<String,Animation> AnimationMap;
	typedef std::map<String,Animation>::iterator AnimationMapIter;

	class K15ENGINE_API AnimatedComponent 
		: public AbstractComponent
	{

	public:
		AnimatedComponent();

		virtual ~AnimatedComponent();

		virtual void setPosition(const Position& position) override;

		virtual void update(U32 gameTime) override;

		bool startAnimation(const String& animationName);

		bool addAnimation(Animation &animation);

		bool handleMessage(Event const &componentEvent);

		AbstractComponent *clone();

		bool removeAnimation(const String &name);

	private:
		AnimationMap m_animationMap;
		AnimationMapIter m_curAnimation;

	};
}

#endif // __ANIMATEDCOMPONENT__
