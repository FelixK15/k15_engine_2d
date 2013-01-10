#include "CollisionComponent.h"
#include "CollisionManager.h"
using namespace K15_Engine;

CollisionComponent::CollisionComponent()
	: AbstractComponent("CollisionComponent")
{
	CollisionManager::subscribe(this);
	setActive(true);
}

CollisionComponent::CollisionComponent( const CollisionComponent& component )
	: AbstractComponent("CollisionComponent")
{
	m_active = component.m_active;
	m_debug = component.m_debug;
	m_hitBoxPosition = component.m_hitBoxPosition;
	m_hitBoxSize = component.m_hitBoxSize;
	setActive(true);

	CollisionManager::subscribe(this);
}

CollisionComponent::~CollisionComponent()
{
	CollisionManager::remove(this);
}

CollisionComponent * CollisionComponent::clone()
{
	return new CollisionComponent(*this);
}

bool CollisionComponent::handleMessage( const Event &gameEvent )
{
	return true;
}

void CollisionComponent::setHitBoxAngle( S16 angle )
{
	
}

void CollisionComponent::update( U32 gameTime )
{

}

void CollisionComponent::setSize( const Size& size )
{
	
}

void CollisionComponent::setPosition( const Position& position )
{
	Position tempPosition;
	tempPosition.setX(position.getX() - m_hitBoxPosition.getX());
	tempPosition.setY(position.getY() - m_hitBoxPosition.getY());
	tempPosition = m_hitBoxPosition + tempPosition;
	m_hitBoxPosition = tempPosition;
}