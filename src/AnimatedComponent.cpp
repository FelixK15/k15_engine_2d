///////////////////////////////////////////////////////////
//  AnimatedComponent.cpp
//  Implementation of the Class AnimatedComponent
//  Created on:      17-Aug-2011 22:18:02
//  Original author: Felix Klinge
///////////////////////////////////////////////////////////

#include "AnimatedComponent.h"
#include "Events.h"
#include "Log.h"
#include "IGraphic.h"

using namespace K15_Engine;

AnimatedComponent::AnimatedComponent()
	: AbstractComponent("AnimatedComponent")
{
	m_curAnimation = m_animationMap.end();
}

AnimatedComponent::~AnimatedComponent()
{
	m_animationMap.clear();
}

void AnimatedComponent::setPosition( const Position& position )
{
	int x = position.getX();
	int y = position.getY();

	for(AnimationMapIter i = m_animationMap.begin();i != m_animationMap.end();i++){
		(*i).second.setNewPosition(x,y);
	}
}

bool AnimatedComponent::addAnimation(Animation &animation)
{
	if(m_animationMap.find(animation.getName().c_str()) == m_animationMap.end()){
		//m_animationMap[animation->getName()] = animation;
		m_animationMap.insert(std::pair<String,Animation>(animation.getName(),animation));
		m_curAnimation = m_animationMap.begin();
	}else{
		WRITE_ERRORLOG("Couldn't add animation. Animation with the same name has been added before.");

		return false;
	}

	return true;
}

bool AnimatedComponent::startAnimation( const String& animationName )
{
	AnimationMapIter newAnimation = m_animationMap.find(animationName);

	if(animationName.empty() || newAnimation == m_animationMap.end()){
		WRITE_ERRORLOG("Can't find an animation with the name \"" + animationName + "\".");

		return false;
	}else{
		m_curAnimation = newAnimation;
	}

	return true;
}

bool AnimatedComponent::handleMessage( Event const &componentEvent )
{
	if(componentEvent.getType() == Events::ObjectMoved){
		int x = componentEvent.getArgument("x").toInteger;
		int y = componentEvent.getArgument("y").toInteger;

		for(AnimationMapIter i = m_animationMap.begin();i != m_animationMap.end();i++){
			(*i).second.setNewPosition(x,y);
		}

		return true;
	}

	if(componentEvent.getType() == Events::NewAlpha){
		int newAlpha = componentEvent.getArgument("alpha").toInteger;

		for(AnimationMapIter i = m_animationMap.begin();i != m_animationMap.end();i++){
			AnimationList *curList = &(*i).second.m_animationList;
			for(AnimationList::iterator j = curList->begin();j != curList->end();j++){
				(*j).m_graphic->setAlpha(newAlpha);
			}
		}

		return true;
	}

	if(componentEvent.getType() == Events::NewColor){
		U8 r = componentEvent.getArgument("r").toInteger;
		U8 g = componentEvent.getArgument("g").toInteger;
		U8 b = componentEvent.getArgument("b").toInteger;
		U8 a = componentEvent.getArgument("a").toInteger;

		Color newColor(r,g,b,a);

		for(AnimationMapIter i = m_animationMap.begin();i != m_animationMap.end();i++){
			AnimationList *curList = &(*i).second.m_animationList;
			for(AnimationList::iterator j = curList->begin();j != curList->end();j++){
				(*j).m_graphic->fillWithColor(newColor);
			}
		}

		return true;
	}

	if(componentEvent.getType() == Events::RestoreOriginalGraphic){
		for(AnimationMapIter i = m_animationMap.begin();i != m_animationMap.end();i++){
			AnimationList *curList = &(*i).second.m_animationList;
			for(AnimationList::iterator j = curList->begin();j != curList->end();j++){
				(*j).m_graphic->restoreOriginal();
			}
		}
	}

	if(componentEvent.getType() == Events::NewAnimation){

		String animationName = componentEvent.getArgument("Name").toString;

		return startAnimation(animationName);
	}

	return false;
}

AbstractComponent *AnimatedComponent::clone()
{
	AnimatedComponent *retComponent = new AnimatedComponent();
	for(AnimationMapIter i = m_animationMap.begin();i != m_animationMap.end();i++){
		Animation animation((*i).second);
		retComponent->addAnimation(animation);
	}

	return retComponent;
}

bool AnimatedComponent::removeAnimation(const String &name)
{
	AnimationMap::iterator iter = m_animationMap.find(name);
	if(iter != m_animationMap.end()){
		m_curAnimation = m_animationMap.erase(iter);
	}else{
		WRITE_ERRORLOG("Couldn't remove animation because there's no animation with the name \"" + name + "\"");
		return false;
	}

	return true;
}

void AnimatedComponent::update(U32 gameTime)
{
	if(m_curAnimation != m_animationMap.end()){
		(*m_curAnimation).second.update(gameTime);
	}
}
