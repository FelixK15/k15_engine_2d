///////////////////////////////////////////////////////////
//  Animation.h
//  Implementation of the Class Animation
//  Created on:      15-Aug-2011 23:50:55
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#ifndef __ANIMATION__
#define __ANIMATION__

#include "AnimationData.h"
#include "Position.h"
#include "Event.h"

namespace K15_Engine
{
	typedef std::list<AnimationData> AnimationList;
	typedef std::list<AnimationData>::iterator AnimationListIter;

	class K15ENGINE_API Animation
	{

	friend class AnimatedComponent;
	
	public:
		Animation(const Animation &anim);

		Animation(const String &name);

		virtual ~Animation();

		void addAnimationData(AnimationData &animationdata);

		void setNewPosition(Position position);

		void setNewPosition(int x,int y);

		const String &getName() const;

		void update(U32 deltaTime);

	private:
		AnimationList m_animationList;
		AnimationListIter m_currentAnimationData;
		const String m_name;

	};
}

#endif // __ANIMATION__
