
#ifndef __MYGAME__HEADER__
#define __MYGAME__HEADER__

#include "Game.h"
#include "GameObject.h"
#include "ComponentFactory.h"
#include "IEventListener.h"
#include "Events.h"
#include "EventManager.h"
#include "AbstractComponent.h"
#include "Camera.h"

using namespace K15_Engine;

class LolGame : public Game , public IEventListener
{
public:

	virtual void start() override{
		ADD_LISTENER(this,Events::KeyboardPressed);

		GraphicPtr graphic = myGame->getGraphicManager()->createGraphic("Test1.png");

		VariantList paramList;
		paramList.push_back(Variant(graphic));

		AbstractComponent* component = ComponentFactory::create("RenderableComponent",paramList);
		m_gameObject.addComponent(component);
		m_gameObject.autoUpdate(true);

		getGraphicManager()->createCamera();
		Game::start();
	}

	virtual bool handleEvent(Event const &gameEvent) override{
		if(gameEvent.getType() == Events::KeyboardPressed){
			short key = gameEvent.getArgument("key").toInteger;

			if(key == K15_SPACE){
				getGraphicManager()->getCamera(0)->zoom();
			}else if(key == K15_ENTER){
				getGraphicManager()->getCamera(1)->zoom();
			}

			return true;
		}

		return false;
	}

	virtual void stop() override{
		Game::stop();
		REMOVE_LISTENER(this,Events::KeyboardPressed);
	}

private:
	GameObject m_gameObject;
};

#endif //__MYGAME__HEADER__