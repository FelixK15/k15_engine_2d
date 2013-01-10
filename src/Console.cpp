#include "Console.h"
#include "IGraphic.h"
#include "IFont.h"
#include "Rectangle.h"
#include "Events.h"
#include "LuaCommand.h"
#include "ConfigFile.h"
#include "EventManager.h"
#include "Log.h"

#include "Game.h"

using namespace K15_Engine;

template<> Console *Singleton<Console>::m_instance = 0;

Console::Console() : m_isOpen(false)
{
	ADD_LISTENER(this,Events::KeyboardPressed);
	ADD_LISTENER(this,Events::MessageLogged);
	m_toggleKey = '`';
	m_userInput.setPosition(0,200);

	m_userInput.setFont(_CONSOLE_FONT);

	int r = _CONSOLE_FONT_COLOR[0];
	int g = _CONSOLE_FONT_COLOR[1];
	int b = _CONSOLE_FONT_COLOR[2];
	int a = _CONSOLE_FONT_COLOR[3];

	m_userInput.setColor(Color(r,g,b,a));

	_loadBackground();

	_loadInputBackground();
}

Console::~Console()
{
	_close();
	REMOVE_LISTENER(this,Events::KeyboardPressed);
	REMOVE_LISTENER(this,Events::MessageLogged);
}

bool Console::update( U32 deltaTime )
{
	DRAW_GRAPHIC(m_background);
	DRAW_GRAPHIC(m_inputBackground);

	std::for_each(m_entries.begin(),m_entries.end(),[&deltaTime](DrawableString& go){
		go.update(deltaTime);	
	});

	m_userInput.update(deltaTime);
	return true;
}

bool Console::handleEvent( Event const &gameEvent )
{
	if(gameEvent.getType() == Events::KeyboardPressed){
		_processSimpleInput(gameEvent.getArgument("key").toInteger);
	}else if(gameEvent.getType() == Events::UnicodeKeyboardPressed){
		_processInput(gameEvent.getArgument("key").toInteger);
	}else if(gameEvent.getType() == Events::MessageLogged){
		addEntry(Log::getLatestEntry());
	}

	return true;
}

void Console::addEntry( LogEntry entry )
{
	if(entry.getPriority() > 2){
		DrawableString newEntry(entry.getMessage());
		if(entry.getPriority() == kError){
			newEntry.setColor(Color::Yellow);
		}else if(entry.getPriority() == kCritical){
			newEntry.setColor(Color::Red);
		}else if(entry.getPriority() == kLua){
			newEntry.setColor(Color::Blue);
		}else if(entry.getPriority() == kNormal){
			newEntry.setColor(Color::White);
		}

		newEntry.setFont(_CONSOLE_FONT);
		newEntry.getFont()->setSize(20);
		newEntry.setMargin(8);

		m_entries.push_back(newEntry);
	
		while(m_entries.size() > 8){
			m_entries.pop_back();
		}
	
		_realignPositions();
	}
}

void Console::_open()
{
	m_isOpen = true;

 	ADD_LISTENER(this,Events::UnicodeKeyboardPressed);
}

void Console::_close()
{
	m_isOpen = false;

	REMOVE_LISTENER(this,Events::UnicodeKeyboardPressed);
}

void Console::_realignPositions()
{
	int margin = 0;
	for(ConsoleEntries::iterator i = m_entries.begin();i != m_entries.end();i++){
		margin += i->getSize().getHeight();
		i->setPosition(0,margin);
	}
}

void Console::_processInput( const U16 input )
{
	if(isOpen()){
		m_userInput += input;
	}
}

void Console::_saveUserInput(const String& input)
{
	this->addEntry(LogEntry("Echo: " + input,kNormal));

// 	LuaCommand command(input);
// 	if(!command.execute()){
// 		this->addEntry(LogEntry(command.getErrorMessage(),kLua));
// 	}
}

void Console::_processSimpleInput(const char input)
{
	if(input == getToggleKey()){
		if(isOpen()){
			_close();
		}else{
			_open();
		}
	}

	if(input == K15_BACKSPACE){
		m_userInput.erase(m_userInput.size() - 1,1);
	}else if(input == K15_ENTER){
		if(!m_userInput.empty()){
			_saveUserInput(m_userInput.getString());
			m_userInput.erase(0,m_userInput.size());
		}
	}
}

Console * Console::getInstance()
{
	return m_instance;

	void _loadBackground();

}

void Console::_loadBackground()
{
	int r = _CONSOLE_BACKGROUND_COLOR[0];;
	int g = _CONSOLE_BACKGROUND_COLOR[1];
	int b = _CONSOLE_BACKGROUND_COLOR[2];
	int a = _CONSOLE_BACKGROUND_COLOR[3];
	
	m_background = myGame->getGraphicManager()->createGraphic(Size(_SCREENWIDTH,200),Position(0,0),Color(r,g,b));

	if(!m_background->loadedSuccessful()){
		//if background couldn't get loaded, just use a black rectangle.
		m_background = myGame->getGraphicManager()->createGraphic(Size(_SCREENWIDTH,200));
	}

	m_background->attachToScreen();
	m_background->setDrawOutOfBounds(true);
}

void Console::_loadInputBackground()
{
	m_inputBackground = myGame->getGraphicManager()->createGraphic(Size(_SCREENWIDTH,20));
	
	m_inputBackground->setPosition(0,200);
	m_inputBackground->attachToScreen();
	m_inputBackground->setDrawOutOfBounds(true);
}