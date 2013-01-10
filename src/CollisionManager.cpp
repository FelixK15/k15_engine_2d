#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "Log.h"

using namespace K15_Engine;

CollisionComponentList CollisionManager::m_componentList;
GenericCollisionMap CollisionManager::m_genericCollisionMap;
SpecificCollisionMap CollisionManager::m_specificCollisionMap;

void saveCollideObjects(CollisionComponentList::iterator begin,CollisionComponentList::iterator end,CollisionComponent* component,std::list<CollisionComponent*> *list)
{
	for(CollisionComponentList::iterator i = begin;i != end;i++){
		CollisionComponent* listComponent = (*i);

		if(listComponent->getParent() != NULL && component->getParent() != NULL){
			if(listComponent != component){
				Position position1 = listComponent->getHitBoxPosition();
				Position position2 = component->getHitBoxPosition();
				Size size1 = listComponent->getHitBoxSize();
				Size size2 = component->getHitBoxSize();

				if(position1.getX() >= position2.getX() && position1.getX() <= position2.getX() + size2.getWidth()){
					if(position2.getX() + size2.getWidth() >= position1.getX() && position2.getX() + size2.getWidth() <= position1.getX() + size1.getWidth()){
						if(position1.getY() >= position2.getY() && position1.getY() <= position2.getY() + size2.getHeight()){
							if(position2.getY() + size2.getHeight() >= position1.getY() && position2.getY() + size2.getHeight() <= position1.getY() + size1.getHeight()){
 								list->push_back(listComponent);
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::update()
{
	for(CollisionComponentList::iterator iter = m_componentList.begin();iter != m_componentList.end();iter++){
		CollisionComponent* component2 = (*iter);

		//Temp list with all CollisionCompontens the current component (component2) collided with..
		std::list<CollisionComponent*> collideObjects;

		//Temp list gets filled.
		saveCollideObjects(m_componentList.begin(),m_componentList.end(),component2,&collideObjects);

		//Go through all collided components and check if there are any collision subscriptions for them.
		for(std::list<CollisionComponent*>::iterator j = collideObjects.begin();j != collideObjects.end();j++){
		
			CollisionComponent* component1 = (*j);

			//Save IDs
			U32 ID1 = component1->getParent()->getID();
			U32 ID2 = component2->getParent()->getID();

			//Save Types
			const String& type1 = component1->getParent()->getType();
			const String& type2 = component2->getParent()->getType();
			
			for(int i = 0; i != 4;i++){
				//Set the findResults to the end of each map.
				GenericCollisionMap::iterator findResultGeneric = m_genericCollisionMap.end();
				SpecificCollisionMap::iterator findResultSpecific = m_specificCollisionMap.end();

				if(i == 0){
					//Look for ID accordance
					findResultSpecific = m_specificCollisionMap.find(std::pair<int,int>(ID1,ID2));
				}else if(i == 1){
					//Look for ID accordance (reversed)
					findResultSpecific = m_specificCollisionMap.find(std::pair<int,int>(ID2,ID1));
				}else if(i == 2){
					//Look for Type accordance
					findResultGeneric = m_genericCollisionMap.find(std::pair<String,String>(type1,type2));
				}else if(i == 3){
					//Look for Type accordance(reversed)
					findResultGeneric = m_genericCollisionMap.find(std::pair<String,String>(type2,type1));
				}

				//Found something? (!= end())
				if(findResultGeneric != m_genericCollisionMap.end() || findResultSpecific != m_specificCollisionMap.end()){
					CollisionHandler handler = (findResultGeneric == m_genericCollisionMap.end() ? findResultSpecific->second : findResultGeneric->second);

					//Set as collided (to determine which component exactly collided, because there's maybe more then one CollisionComponent per GameObject)
					component1->setCollided(true);
					component2->setCollided(true);

					//Call the handler
					handler(component1->getParent(),component2->getParent());
					//handler(component2->getParent(),component1->getParent());

					//Unset the components.
					component1->setCollided(false);
					component2->setCollided(false);

					break;
				}
			}
		}
	}
}

void CollisionManager::subscribeCollisionHandler(const String& GameObjectType1,const String& GameObjectType2,CollisionHandler handler )
{
	m_genericCollisionMap.insert(std::pair<std::pair<String,String>,CollisionHandler>(std::pair<String,String>(GameObjectType1,GameObjectType2),handler));
}

void CollisionManager::subscribeSpecificCollisionHandler( int GameObjectID1,int GameObjectID2,CollisionHandler handler )
{
	m_specificCollisionMap.insert(std::pair<std::pair<int,int>,CollisionHandler>(std::pair<int,int>(GameObjectID1,GameObjectID2),handler));
}

void CollisionManager::subscribe( CollisionComponent* component )
{
	m_componentList.push_back(component);
}

void CollisionManager::remove( CollisionComponent* component )
{
	m_componentList.remove(component);
}
