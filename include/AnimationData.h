///////////////////////////////////////////////////////////
//  AnimationData.h
//  Implementation of the Class AnimationData
//  Created on:      16-Aug-2011 21:00:08
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#ifndef	__ANIMATIONDATA__
#define __ANIMATIONDATA__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API AnimationData
	{

	friend class Animation;
	friend class AnimatedComponent;

	public:
		
		AnimationData(const String &resourceName,U32 frameTimeMS);

		AnimationData(GraphicPtr graphic,U32 frameTimeMS);

		AnimationData(const AnimationData &animData);

		virtual ~AnimationData();

		void setFrameTime(int ms);

		int getFrameTime();

	private:
		U32 m_frameTimeOrigin;
		U32 m_frameTimeMS;
		GraphicPtr m_graphic;

	};
}


#endif __ANIMATIONDATA__
