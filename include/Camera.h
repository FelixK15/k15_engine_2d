/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * 
 */
#pragma once

#ifndef __CAMERA__
#define __CAMERA__

#include "StandardIncludes.h"

#include "IEventListener.h"
#include "GameObject.h"
#include "Size.h"
#include "Position.h"

namespace K15_Engine
{
	typedef std::list<GraphicPtr> GraphicList;

	class K15ENGINE_API Camera : public GameObject , public IEventListener
	{
	public:
		Camera();

		Camera(const Size& size,const Position& position);

		Camera(const Size& size,const Position& position,const Position& screenposition);

		Camera(const Camera& camera);

		virtual ~Camera();

		void zoom();

		void fixToGameObject(GameObject *gameobject);

		const Position& getScreenPosition(){return m_screenPosition;}

		void setScreenPosition(const Position& position){m_screenPosition = position;}

		void addGraphic(GraphicPtr graphic);

		GraphicList& getGraphics();

		virtual bool update(U32 deltaTime);

		virtual void setDebugMode(bool var);

		virtual bool handleEvent(Event const &gameEvent);

	private:

		void _resetPosition();

		//void preUpdate();

		Position m_screenPosition;

		GameObject *m_target;

		GraphicList m_graphicList;
	};
}

#endif //__CAMERA__