#pragma once

#ifndef __GAME__
#define __GAME__

#include "DLL_Header.h"
#include "Singleton.h"

#include "AbstractFontManager.h"
#include "AbstractGraphicManager.h"
#include "AbstractMessageQueue.h"
#include "AbstractMusicManager.h"
#include "AbstractSoundManager.h"
#include "AbstractSystemManager.h"
#include "ResourceManager.h"
#include "StateMachine.h"

#define myGame K15_Engine::Game::getInstance()

namespace K15_Engine
{
	class K15ENGINE_API Game : public Singleton<Game>
	{

	public:
		Game();

		virtual ~Game();

		virtual bool initialize();

		virtual void shutdown();

		virtual void update();

		virtual void start(){m_running = true;update();}

		virtual void stop(){m_running = false;}

		bool isRunning();

		static Game* getInstance(){return m_instance;}

		//Manager

		AbstractGraphicManager* getGraphicManager(){return m_graphicManager;}

		AbstractFontManager* getFontManager(){return m_fontManager;}

		AbstractMusicManager* getMusicManager(){return m_musicManager;}

		AbstractSoundManager* getSoundManager(){return m_soundManager;}

		AbstractSystemManager* getSystemManager(){return m_systemManager;}

		ResourceManager* getResourceManager(){return m_resourceManager;}

		StateMachine* getStateMachine(){return m_stateMachine;}

	protected:

		bool _loadSubSystem();

		void _waitForFPS(int deltaTime);

		IEngineSubSystem *m_subsystem;

		AbstractWindow *m_window;

		AbstractGraphicManager *m_graphicManager;

		AbstractSoundManager *m_soundManager;

		AbstractMusicManager *m_musicManager;

		AbstractMessageQueue *m_messageQueue;

		AbstractFontManager *m_fontManager;

		AbstractSystemManager *m_systemManager;

		EventManager *m_eventManager;

		ResourceManager *m_resourceManager;

		StateMachine *m_stateMachine;

//		Console *m_console;

		int m_lastUpdated;

		bool m_running;

		bool m_debug;
	};
}

#endif // __GAME__
