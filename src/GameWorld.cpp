#include "GameWorld.h"
#include "Log.h"

using namespace K15_Engine;

namespace{
	const int UNDEFINED_LAYER_INDEX = -999999;
}

GameWorld::GameWorld()
	: m_name(""),
	  m_collisionLayerIndex(UNDEFINED_LAYER_INDEX)
{

}

GameWorld::GameWorld( const GameWorld &gameWorld )
	: m_collisionLayerIndex(UNDEFINED_LAYER_INDEX)
{
	_copy(gameWorld);
}

GameWorld::~GameWorld()
{
	m_layerList.clear();
}

const String& GameWorld::getName() const
{
	return m_name;
}

void GameWorld::setSize( int width,int height )
{
	m_size = Size(width,height);
}

void GameWorld::setSize(const Size& size)
{
	m_size = size;
}

void GameWorld::update(U32 deltaTime)
{
	std::for_each(m_layerList.begin(),m_layerList.end(),[&deltaTime](GameWorldLayer &layer){
		layer.update(deltaTime);
	});
}

int GameWorld::addLayer( const GameWorldLayer& layer )
{
	m_layerList.push_back(layer);

	if(layer.isCollisionLayer()){
		m_collisionLayerIndex = m_layerList.size();
	}

	return m_layerList.size();
}

bool GameWorld::removeLayer( const String& name )
{
	for(LayerList::iterator i = m_layerList.begin();i != m_layerList.end();i++){
		if(i->getName() == name){
			i = m_layerList.erase(i);

			if(i == m_layerList.end()){
				return true;
			}
		}
	}

	WRITE_DEBUG("No layer with the name \"" + name + "\" has been found.");

	return false;
}

bool GameWorld::removeLayer( U32 layerPosition )
{
	if(layerPosition > m_layerList.size()){
		return false;
	}

	//m_layerList.erase(m_layerList.begin() + layerPosition);
	return true;
}

GameWorldLayer* GameWorld::getLayer( int layerID )
{
	if(m_collisionLayerIndex != UNDEFINED_LAYER_INDEX){
		if(layerID == 0){
			layerID = m_collisionLayerIndex;
		}else if(layerID != 0){
			layerID = m_collisionLayerIndex + layerID;
		}
	}
	
	if(layerID > m_layerList.size() || layerID < 0){
		WRITE_ERRORLOG("layerID is greater than size of layers.");
		return NULL;
	}else{
		return &m_layerList.at(layerID);
	}
}

GameWorldLayer* GameWorld::getLayer( const String& layerName )
{
	for(LayerList::iterator i = m_layerList.begin();i != m_layerList.end();i++){
		const String& curLayerName = (*i).getName();

		if(curLayerName == layerName){
			return &(*i);
		}
	}

	WRITE_ERRORLOG("Layer with the name \"" + layerName + "\" was not found.");
	return NULL;
}

GameWorld &GameWorld::operator=( const GameWorld &gw )
{
	_copy(gw);
	
	return *this;
}

void GameWorld::_copy( const GameWorld &gw )
{
	this->m_name = gw.m_name;
	this->m_size = gw.m_size;
	this->m_layerList = gw.m_layerList;
}
