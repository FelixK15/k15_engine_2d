#include "AnimationData.h"
#include "IGraphic.h"

#include "Game.h"

using namespace K15_Engine;

AnimationData::AnimationData( const String &resourceName,U32 frameTimeMS )
{

}


AnimationData::AnimationData(GraphicPtr graphic,U32 frameTimeMS)
	: m_frameTimeOrigin(frameTimeMS),
	m_graphic(myGame->getGraphicManager()->createGraphic()),
	m_frameTimeMS(frameTimeMS)
{
	m_graphic->copyFrom(static_cast<IResourceable*>(graphic.get()));
	m_graphic->setVisible(false);
}

AnimationData::AnimationData( const AnimationData &animData )
{
	this->m_frameTimeMS = animData.m_frameTimeMS;
	this->m_frameTimeOrigin = animData.m_frameTimeOrigin;
	this->m_graphic = animData.m_graphic;
}

AnimationData::~AnimationData()
{
	
}

void AnimationData::setFrameTime( int ms )
{
	m_frameTimeOrigin = ms;
	m_frameTimeMS = ms;
}

int AnimationData::getFrameTime()
{
	return m_frameTimeMS;
}
