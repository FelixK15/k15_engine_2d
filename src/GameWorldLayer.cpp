#include "GameWorldLayer.h"

using namespace K15_Engine;


GameWorldLayer::GameWorldLayer()
{
	m_name = "";
	m_scrollSpeed = 1.0f;
	m_collisionLayer = false;
}

GameWorldLayer::GameWorldLayer( const String& name )
{
	m_name = name;
	m_scrollSpeed = 1.0f;
	m_collisionLayer = false;
}

GameWorldLayer::GameWorldLayer( const GameWorldLayer &layer )
{
	m_name = layer.m_name;
	m_scrollSpeed = layer.m_scrollSpeed;
	m_collisionLayer = layer.m_collisionLayer;
	m_gameObjectList = layer.m_gameObjectList;
}

GameWorldLayer::~GameWorldLayer()
{
	m_gameObjectList.clear();
}

void GameWorldLayer::update( U32 deltaTime )
{
	std::for_each(m_gameObjectList.begin(),m_gameObjectList.end(),[&deltaTime](GameObject &gameObject){
		gameObject.update(deltaTime);
	});
}

void GameWorldLayer::setName( const String& name )
{
	m_name = name;
}

const String& GameWorldLayer::getName() const
{
	return m_name;
}

bool GameWorldLayer::isCollisionLayer() const
{
	return m_collisionLayer;
}

void GameWorldLayer::setAsCollisionLayer()
{
	m_collisionLayer = true;
}

F32 GameWorldLayer::getScrollSpeed() const
{
	return m_scrollSpeed;
}

void GameWorldLayer::setScrollSpeed( F32 scrollSpeed )
{
	m_scrollSpeed = scrollSpeed;
}

void GameWorldLayer::addGameObject( GameObject &gameObject )
{
	m_gameObjectList.push_back(gameObject);
}
