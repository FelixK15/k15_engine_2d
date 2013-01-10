/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it like you want.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND COMES WITHOUT ANY
 * WARRANTIES
 *
 * @section DESCRIPTION
 *
 * 
 */

#ifndef __RENDERABLE_COMPONENT__
#define __RENDERABLE_COMPONENT__

#include "AbstractComponent.h"

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API RenderableComponent : public AbstractComponent
	{
	public:

		RenderableComponent(const String& rsgraphic);

		RenderableComponent(GraphicPtr graphic);

		void setGraphic(GraphicPtr graphic){m_graphic = graphic;}

		void setGraphic(const String& graphicResource);

		virtual AbstractComponent *clone() override;

		virtual bool handleMessage(const Event &gameEvent ) override;

		virtual void setSize(const Size& size) override;

		virtual void setPosition(const Position& position) override;

		virtual void setAngle(S16 angle) override;

		virtual void update(U32 gameTime) override;

	private:
		
		GraphicPtr m_graphic;

	};
}

#endif //__RENDERABLE_COMPONENT__
