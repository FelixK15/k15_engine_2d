#include "VersatileComponent.h"

using namespace K15_Engine;

VersatileComponent::VersatileComponent(String type,HandleMessageFunction handleEventFunction,UpdateFunction updateFunction)
	: AbstractComponent(type),
	  m_handleMessageFunction(handleEventFunction),
	  m_updateFunction(updateFunction),
	  m_startFunction([](GameObject *object){}),
	  m_shutdownFunction([](GameObject *object){})
{

}

VersatileComponent::VersatileComponent(String type,StartFunction startFunction,HandleMessageFunction handleEventFunction,UpdateFunction updateFunction)
	: AbstractComponent(type),
	m_handleMessageFunction(handleEventFunction),
	m_updateFunction(updateFunction),
	m_startFunction(startFunction),
	m_shutdownFunction([](GameObject *object){})
{

}

VersatileComponent::VersatileComponent(String type,StartFunction startFunction,ShutdownFunction shutdownFunction,HandleMessageFunction handleEventFunction,UpdateFunction updateFunction)
	: AbstractComponent(type),
	m_handleMessageFunction(handleEventFunction),
	m_updateFunction(updateFunction),
	m_startFunction(startFunction),
	m_shutdownFunction(shutdownFunction)
{

}

VersatileComponent::VersatileComponent(const VersatileComponent &vComponent)
	: AbstractComponent(vComponent.getType())
{
	this->m_shutdownFunction = vComponent.m_shutdownFunction;
	this->m_startFunction = vComponent.m_startFunction;
	this->m_updateFunction = vComponent.m_updateFunction;
	this->m_handleMessageFunction = vComponent.m_handleMessageFunction;
}

VersatileComponent::~VersatileComponent()
{

}

GameObject * VersatileComponent::getParent()
{
	return m_parent;
}

void VersatileComponent::start()
{
	m_startFunction(m_parent);
}

void VersatileComponent::update( U32 gameTime )
{
	m_updateFunction(gameTime,m_parent);
}

bool VersatileComponent::handleMessage( Event const & componentEvent )
{
	return m_handleMessageFunction(componentEvent,m_parent);
}

AbstractComponent * VersatileComponent::clone()
{
	VersatileComponent *vComponent = new VersatileComponent(*this);
	return static_cast<AbstractComponent*>(vComponent);
}

void VersatileComponent::shutdown()
{
	m_shutdownFunction(m_parent);
}
