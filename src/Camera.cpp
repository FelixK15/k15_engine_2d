#include "Camera.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Events.h"
#include "IGraphic.h"

using namespace K15_Engine;

Camera::Camera()
	: GameObject("Camera")
{

}

Camera::Camera(const Size& size,const Position& position)
	: GameObject("Camera")
{
	m_size = size;
	m_position = position;
// 
// 	ADD_LISTENER(this,Events::KeyboardPressed);
// 	ADD_LISTENER(this,Events::KeyboardReleased);
}

Camera::Camera(const Size& size,const Position& position,const Position& screenposition)
	: GameObject("Camera")
{
	m_size = size;
	m_position = position;
	m_screenPosition = position;
// 
// 	ADD_LISTENER(this,Events::KeyboardPressed);
// 	ADD_LISTENER(this,Events::KeyboardReleased);
}

Camera::Camera(const Camera& camera)
	: GameObject(camera)
{

}

Camera::~Camera()
{
	REMOVE_LISTENER(this,Events::KeyboardPressed);
	REMOVE_LISTENER(this,Events::KeyboardReleased);
}

void Camera::fixToGameObject( GameObject *gameobject )
{
	m_target = gameobject;
}

void Camera::addGraphic( GraphicPtr graphic )
{
	m_graphicList.push_back(graphic);
}

GraphicList& Camera::getGraphics()
{
	return m_graphicList;
}

bool Camera::update( U32 deltaTime )
{
	if(m_target != NULL){
		m_positionNextTick = m_target->getPosition();
	}

	return GameObject::update(deltaTime);
}

void Camera::setDebugMode( bool var )
{
	if(var){
		ADD_LISTENER(this,Events::KeyboardPressed);
		ADD_LISTENER(this,Events::KeyboardReleased);
	}else{
		REMOVE_LISTENER(this,Events::KeyboardPressed);
		REMOVE_LISTENER(this,Events::KeyboardReleased);
	}
}

bool Camera::handleEvent( Event const &gameEvent )
{
	if(gameEvent.getType() == Events::KeyboardPressed){
		U16 key = gameEvent.getArgument("key").toInteger;
		
		if(key == K15_DOWN){
			m_position.setY(m_position.getY()+10);
		}else if(key == K15_UP){
			m_position.setY(m_position.getY()-10);
		}else if(key == K15_LEFT){
			m_position.setX(m_position.getX()-10);
		}else if(key == K15_RIGHT){
			m_position.setX(m_position.getX()+10);
		}else if(key == K15_w){
			m_size.setHeight(m_size.getHeight()+10);
		}else if(key == K15_s){
			m_size.setHeight(m_size.getHeight()-10);
		}else if(key == K15_a){
			m_size.setWidth(m_size.getWidth()+10);
		}else if(key == K15_d){
			m_size.setWidth(m_size.getWidth()-10);
		}

		return true;
	}

	return false;
}

void Camera::zoom()
{

}