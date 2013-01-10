#include "Game.h"
#include "Debug.h"
#include "Events.h"
#include "CollisionManager.h"
#include "ConfigFile.h"
#include "LuaScript.h"
#include "DynamicLibrary.h"
#include "IEngineSubSystem.h"
#include "UsefulMakros.h"

#include "Globals.h"

#include "ComponentFactory.h"
#include "GameObjectManager.h"

#include "Log.h"

#include "Console.h"
#include "EventManager.h"

#include <string>
#include <vector>

using namespace K15_Engine;

template<> Game* Singleton<Game>::m_instance = 0;

typedef IEngineSubSystem* (*EngineSubSystemCreator) ();

#define EXECUTE_LUA_SCRIPTS_IN_VECTOR(vector)	std::for_each(vector.begin(),vector.end(),[](const std::string& file){				\
												LuaScript script(file);																\
												script.execute();})																	\


int draw = 0;

//load values from the config files and save them in the global variables (ugly, I know).
void loadConfigValues();

bool Game::_loadSubSystem()
{
	DynamicLibrary lib(_ENGINE_SUBSYSTEM);

	if(lib.hasBeenLoaded()){
		EngineSubSystemCreator function;
		function = (EngineSubSystemCreator)lib.getFunction("createEngineSubSystem");

		m_subsystem = function();

		m_graphicManager = m_subsystem->createGraphicManager();
		m_soundManager = m_subsystem->createSoundManager();
		m_musicManager = m_subsystem->createMusicManager();
		m_messageQueue = m_subsystem->createInputManager();
		m_fontManager = m_subsystem->createFontManager();
		m_systemManager = m_subsystem->createSystemManager();

		return true;
	}

	return false;
}

Game::Game()
{
	m_lastUpdated = 0;

	m_debug = false;
	m_running = false;

	Log::initialize();

	m_resourceManager = new ResourceManager();
	m_stateMachine = new StateMachine();
	m_eventManager = new EventManager();

	m_subsystem = NULL;
	m_graphicManager = NULL;
	m_soundManager = NULL;
	m_musicManager = NULL;
	m_messageQueue = NULL;
	m_fontManager = NULL;
	m_systemManager = NULL;

	ConfigFile::loadConfigFile();
	loadConfigValues();
}

Game::~Game()
{
//	SAFE_DELETE(m_console);
	SAFE_DELETE(m_fontManager);
	SAFE_DELETE(m_messageQueue);
	SAFE_DELETE(m_stateMachine);
	SAFE_DELETE(m_resourceManager);
 	SAFE_DELETE(m_musicManager);
 	SAFE_DELETE(m_soundManager);
	SAFE_DELETE(m_eventManager);
	SAFE_DELETE(m_graphicManager);
	SAFE_DELETE(m_systemManager);
	SAFE_DELETE(m_subsystem);

	Log::shutdown();
}

bool Game::initialize()
{
	if(_loadSubSystem()){

		if(!(m_musicManager->initialize() && m_graphicManager->initialize() && m_fontManager->initialize())){
			WRITE_CRITICALLOG("Game initialization failed.");
			return false;
		}

		WRITE_LOG("Game has been initialized on " + DateTime().toDateString());

		m_window = m_graphicManager->createWindow(_SCREENWIDTH,_SCREENHEIGHT,_BPP,_FULLSCREEN,_SCREENCAPTION);
//		m_console = new Console();

		return true;
	}

	WRITE_CRITICALLOG("Couldn't load subsystem. (" + String(_ENGINE_SUBSYSTEM) + ")");

	return false;
}

void Game::update()
{	
	while(isRunning()){
		U32 starttime = m_systemManager->getTick();

		while(m_messageQueue->hasNextMessage()){
			m_messageQueue->processCurrentMessage();
		}

		U32 deltaTime =  starttime - m_lastUpdated;

		m_lastUpdated = starttime;

		m_stateMachine->update(deltaTime);
		m_eventManager->update();

// 		if(m_console->isOpen()){
// 			m_console->update(deltaTime);
// 		}
// 
// 		if(Debug::activated){
// 			Debug::update(deltaTime);
// 		}

		CollisionManager::update();

		m_graphicManager->update();

		GameObjectManager::update(deltaTime);

//		LuaManager::update();
	
		_waitForFPS(deltaTime);
	}
}

void Game::shutdown()
{
	DO_IF_POINTER_NOT_NULL(m_graphicManager,m_graphicManager->shutdown());
	DO_IF_POINTER_NOT_NULL(m_musicManager,m_musicManager->shutdown());
	DO_IF_POINTER_NOT_NULL(m_fontManager,m_fontManager->shutdown());
}

bool Game::isRunning()
{
	return m_running;
}

void Game::_waitForFPS(int deltaTime)
{
	if(deltaTime < 1000 / _FPS){
		m_systemManager->sleep((1000 / _FPS) - deltaTime);
	}
}

void loadConfigValues()
{
	///////////////////CONSOLE SETTINGS/////////////////////////////
	ConfigEntryMap settings = ConfigFile::getValues("CONSOLE_SETTINGS");

	if(M_HAS_ITEM(settings,"console_font")){
		_CONSOLE_FONT = GET_N_CONFIG_VALUE(0,settings,"console_font").toString;
	}
	
	if(M_HAS_ITEM(settings,"console_font_color")){
		if(GET_CONFIG_VALUE(settings,"console_font_color").size() >= 3){
			_CONSOLE_FONT_COLOR[0] = GET_N_CONFIG_VALUE(0,settings,"console_font_color").toInteger;
			_CONSOLE_FONT_COLOR[1] = GET_N_CONFIG_VALUE(1,settings,"console_font_color").toInteger;
			_CONSOLE_FONT_COLOR[2] = GET_N_CONFIG_VALUE(2,settings,"console_font_color").toInteger;
			_CONSOLE_FONT_COLOR[3] = GET_N_CONFIG_VALUE(3,settings,"console_font_color").toInteger;
		}
	}
	
	if(M_HAS_ITEM(settings,"console_background_color")){
		if(GET_CONFIG_VALUE(settings,"console_background_color").size() >= 3){
			_CONSOLE_BACKGROUND_COLOR[0] = GET_N_CONFIG_VALUE(0,settings,"console_background_color").toInteger;
			_CONSOLE_BACKGROUND_COLOR[1] = GET_N_CONFIG_VALUE(1,settings,"console_background_color").toInteger;
			_CONSOLE_BACKGROUND_COLOR[2] = GET_N_CONFIG_VALUE(2,settings,"console_background_color").toInteger;
			_CONSOLE_BACKGROUND_COLOR[3] = GET_N_CONFIG_VALUE(3,settings,"console_background_color").toInteger;
		}
	}
	///////////////////////////////////////////////////////////////

	///////////////////GRAPHIC SETTINGS////////////////////////////
	settings = ConfigFile::getValues("GRAPHIC_SETTINGS");

	if(M_HAS_ITEM(settings,"screen_width")){
		_SCREENWIDTH = GET_N_CONFIG_VALUE(0,settings,"screen_width").toInteger;
	}
	
	if(M_HAS_ITEM(settings,"screen_height")){
		_SCREENHEIGHT = GET_N_CONFIG_VALUE(0,settings,"screen_height").toInteger;
	}
	
	if(M_HAS_ITEM(settings,"bpp")){
		_BPP = GET_N_CONFIG_VALUE(0,settings,"bpp").toInteger;
	}
	
	if(M_HAS_ITEM(settings,"screen_fullscreen")){
		_FULLSCREEN = GET_N_CONFIG_VALUE(0,settings,"screen_fullscreen").toBool;
	}
	
	if(M_HAS_ITEM(settings,"screen_caption")){
		_SCREENCAPTION = GET_N_CONFIG_VALUE(0,settings,"screen_caption").toString;
	}
	
	if(M_HAS_ITEM(settings,"screen_icon")){
		_SCREENICON = GET_N_CONFIG_VALUE(0,settings,"screen_icon").toString;
	}
	///////////////////////////////////////////////////////////////

	///////////////////PROCESS SETTINGS////////////////////////////
	settings = ConfigFile::getValues("PROCESS_SETTINGS");

	if(M_HAS_ITEM(settings,"multithreaded_inputhandling")){
		_MULTITHREADED_INPUTHANDLING = GET_N_CONFIG_VALUE(0,settings,"multithreaded_inputhandling").toBool;
	}
	
	if(M_HAS_ITEM(settings,"multithreaded_eventhandling")){
		_MULTITHREADED_EVENTMESSAGING = GET_N_CONFIG_VALUE(0,settings,"multithreaded_eventhandling").toBool;
	}
	
	if(M_HAS_ITEM(settings,"max_fps")){
		_FPS = GET_N_CONFIG_VALUE(0,settings,"max_fps").toInteger;
	}
	
	if(M_HAS_ITEM(settings,"engine_subsystem")){
		_ENGINE_SUBSYSTEM = GET_N_CONFIG_VALUE(0,settings,"engine_subsystem").toString;
	}
	///////////////////////////////////////////////////////////////

	///////////////////RESOURCE SETTINGS////////////////////////////
	settings = ConfigFile::getValues("RESOURCE_SETTINGS");

	if(M_HAS_ITEM(settings,"resourcefile")){
		_RESOURCEFILE = GET_N_CONFIG_VALUE(0,settings,"resourcefile").toString;
	}
	
	if(M_HAS_ITEM(settings,"size_of_resource_cache_in_bytes")){
		_SIZE_RESOURCE_CACHE = GET_N_CONFIG_VALUE(0,settings,"size_of_resource_cache_in_bytes").toInteger;
	}
	///////////////////////////////////////////////////////////////
}