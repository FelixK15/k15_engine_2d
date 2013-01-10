
#pragma once

#ifndef __GAMEWORLDLAYER__
#define __GAMEWORLDLAYER__

#include "StandardIncludes.h"
#include "GameObject.h"

namespace K15_Engine
{
	typedef std::list<GameObject> GameObjectList;

	class K15ENGINE_API GameWorldLayer
	{
	public:
		GameWorldLayer();

		GameWorldLayer(const String& name);

		GameWorldLayer(const GameWorldLayer &layer);

		~GameWorldLayer();

		void update(U32 deltaTime);

		void setName(const String& name);

		const String& getName() const;

		bool isCollisionLayer() const;

		void setAsCollisionLayer();

		F32 getScrollSpeed() const;

		void setScrollSpeed(F32 scrollSpeed);

		void addGameObject(GameObject &gameObject);

	private:

		GameObjectList m_gameObjectList;
		String m_name;
		F32 m_scrollSpeed;
		bool m_collisionLayer;
	};
}

#endif //__CLASSNAME__