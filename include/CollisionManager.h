#pragma once

#ifndef __COLLISIONMANAGER__
#define __COLLISIONMANAGER__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class CollisionComponent;

	typedef std::list<CollisionComponent*> CollisionComponentList;
	typedef std::function<void(GameObject*,GameObject*)> CollisionHandler;
	typedef std::map<std::pair<String,String>,CollisionHandler> GenericCollisionMap;
	typedef std::map<std::pair<int,int>,CollisionHandler> SpecificCollisionMap;

	class K15ENGINE_API CollisionManager
	{
	public:

		static void update();

		static void subscribeCollisionHandler(const String& GameObjectType1,const String& GameObjectType2,CollisionHandler handler);

		static void subscribeSpecificCollisionHandler(int GameObjectID1,int GameObjectID2,CollisionHandler handler);

		static void subscribe(CollisionComponent* component);

		static void remove(CollisionComponent* component);

	private:

		static CollisionComponentList m_componentList;

		static GenericCollisionMap m_genericCollisionMap;

		static SpecificCollisionMap m_specificCollisionMap;

	};
}

#endif //__COLLISIONMANAGER__