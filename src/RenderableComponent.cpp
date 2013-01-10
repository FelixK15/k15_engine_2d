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

#include "RenderableComponent.h"
#include "IGraphic.h"
#include "Game.h"
#include "Events.h"

using namespace K15_Engine;

RenderableComponent::RenderableComponent(const String& rsgraphic)
	: AbstractComponent("RenderableComponent")
{
	Resource *res = myGame->getResourceManager()->getResource(rsgraphic);
	m_graphic = myGame->getGraphicManager()->createGraphic(res);
}

RenderableComponent::RenderableComponent(GraphicPtr graphic)
	: AbstractComponent("RenderableComponent")
{
	m_graphic = graphic;
}

void RenderableComponent::setGraphic(const String& graphicResource)
{
	m_graphic = myGame->getGraphicManager()->createGraphic(graphicResource);
}

AbstractComponent * RenderableComponent::clone()
{
	AbstractComponent *newComponent = new RenderableComponent(m_graphic);

	return newComponent;
}

bool RenderableComponent::handleMessage( const Event &gameEvent )
{
	if(gameEvent.getType() == Events::NewColor){
		int r = gameEvent.getArgument("r").toInteger;
		int g = gameEvent.getArgument("g").toInteger;
		int b = gameEvent.getArgument("b").toInteger;
		int a = gameEvent.getArgument("a").toInteger;

		m_graphic->fillWithColor(r,g,b,a);

		return true;
	}

	return false;
}

void RenderableComponent::setSize( const Size& size )
{
	m_graphic->setSize(size);
}

void RenderableComponent::setPosition( const Position& position )
{
	m_graphic->setPosition(position);
}

void RenderableComponent::setAngle( S16 angle )
{
	m_graphic->rotate(angle);
}

void RenderableComponent::update( U32 gameTime )
{
	DRAW_GRAPHIC(m_graphic);
}