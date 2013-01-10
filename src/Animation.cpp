#include "Animation.h"
#include "IGraphic.h"
#include "EventManager.h"
#include "Events.h"

#include "Game.h"

using namespace K15_Engine;

Animation::Animation( const Animation &anim )
	: m_name(anim.m_name)
{
	std::for_each(anim.m_animationList.begin(),anim.m_animationList.end(),[&](AnimationData animdata){
			this->m_animationList.push_back(AnimationData(animdata));
	});
	
	this->m_currentAnimationData = this->m_animationList.end();
}

Animation::Animation(const String &name)
	: m_name(name)
{
	m_currentAnimationData = m_animationList.end();
}

Animation::~Animation()
{
	m_animationList.clear();
}

void Animation::addAnimationData(AnimationData &animationdata)
{
	m_animationList.push_back(animationdata);
}

void Animation::setNewPosition( Position position )
{
	for(AnimationListIter i = m_animationList.begin();i != m_animationList.end();i++){
		S16 x,y;
		S16 newX,newY;

		newX = position.getX();
		newY = position.getY();

		(*i).m_graphic->getPosition(&x,&y);

		/*if(x < newX){
			newX += newX - x;
		}else if(x > newX){
			newX += x + newX;
		}

		if(y < newY){
			newY += newY - y;
		}else if(y > newY){
			newY += y + newY;
		}*/

		(*i).m_graphic->setPosition(newX,newY);
	}
}

void Animation::setNewPosition( int x,int y )
{
	setNewPosition(Position(x,y));
}

const String &Animation::getName() const{

	return m_name;
}

void Animation::update(U32 deltaTime)
{
	if(m_currentAnimationData == m_animationList.end()){
		m_currentAnimationData = m_animationList.begin();
	}

	if(m_currentAnimationData->m_frameTimeOrigin != 0){
		if(m_currentAnimationData != m_animationList.end()){
			AnimationData &curAnimationData = (*m_currentAnimationData);
			if(curAnimationData.m_frameTimeMS <= deltaTime){
				/*curAnimationData.m_graphic->setVisible(false);*/
				curAnimationData.m_frameTimeMS = curAnimationData.m_frameTimeOrigin;
				m_currentAnimationData++;

				if(m_currentAnimationData == m_animationList.end()){
					NEW_EVENT_WITH_1_ARG(Events::AnimationFinished,"Name",this->m_name);
					EXECUTE_NEW_EVENT_IMMEDIATELY();
					m_currentAnimationData = m_animationList.begin();
				}

				/*(*m_currentAnimationData).m_graphic->setVisible(true);*/
			}else{
				curAnimationData.m_frameTimeMS -= deltaTime;
			}
		}
	}


	DRAW_GRAPHIC(m_currentAnimationData->m_graphic);
}