#pragma once

#ifndef __GAMEOBJECTMANAGER__
#define __GAMEOBJECTMANAGER__

#include "StandardIncludes.h"

namespace K15_Engine
{
	typedef std::map<int,GameObject*> GameObjectMap;

	class K15ENGINE_API GameObjectManager
	{

	public:

		static void update(U32 deltaTime);

		static bool addGameObject(GameObject *object);

		static bool removeGameObject(GameObject *object);

		static GameObject *getObjectByID(int id);

	private:
		static GameObjectMap m_objectsMap;
	};
}

#endif // __GAMEOBJECTMANAGER__
