#include "GameObjectManager.h"
#include "GameObject.h"
#include "Debug.h"
#include "StringConverter.h"
#include "Log.h"

using namespace K15_Engine;

GameObjectMap GameObjectManager::m_objectsMap;

void GameObjectManager::update(U32 deltaTime)
{
	for(GameObjectMap::iterator i = m_objectsMap.begin();i != m_objectsMap.end();i++){
		i->second->update(deltaTime);
	}

	Debug::drawAlignedDebugString(StringConverter::toString(m_objectsMap.size()) + " GameObjects get updated automaticly.");
}

GameObject * GameObjectManager::getObjectByID( int id )
{
	GameObjectMap::iterator i = m_objectsMap.find(id);

	if(i == m_objectsMap.end()){
		WRITE_ERRORLOG("There's no GameObject with the id of " + StringConverter::toString(id));
		return NULL;
	}

	return (*i).second;
}

bool GameObjectManager::addGameObject( GameObject *object )
{
	if(object != NULL){
		m_objectsMap[object->getID()] = object;

		return true;
	}

	WRITE_ERRORLOG("Given object is NULL.");
	return false;
}

bool GameObjectManager::removeGameObject( GameObject *object )
{
	if(object != NULL){

		GameObjectMap::iterator i = m_objectsMap.find(object->getID());
		m_objectsMap.erase(i);

		return true;
	}

	WRITE_ERRORLOG("Given object is NULL.");
	return false;
}