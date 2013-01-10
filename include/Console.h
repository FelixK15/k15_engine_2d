#pragma once

#ifndef __CONSOLE__
#define __CONSOLE__

#include "StandardIncludes.h"
#include "DrawableString.h"
#include "Singleton.h"
#include "LogEntry.h"
#include "IEventListener.h"

namespace K15_Engine
{
	typedef std::list<DrawableString> ConsoleEntries;

	class K15ENGINE_API Console : public GameObject, public IEventListener, public Singleton<Console>
	{

	public:
		Console();

		virtual ~Console();

		bool isOpen() {return m_isOpen;}

		char getToggleKey() {return m_toggleKey;}

		void setToggleKey(char c) {m_toggleKey = c;}

		virtual bool update(U32 deltaTime);

		virtual bool handleEvent( Event const &gameEvent );

		static Console *getInstance();

	private:
		
		void _open();

		void _close();

		void _loadBackground();

		void _loadInputBackground();

		void _realignPositions();

		void _saveUserInput(const String& input);

		void _processInput(const U16 input);

		void _processSimpleInput(const char input);

		void addEntry(LogEntry entry);

		char m_toggleKey;

		bool m_isOpen;

		GraphicPtr m_background;

		GraphicPtr m_inputBackground;

		DrawableString m_userInput;
		
		ConsoleEntries m_entries;
		
	};
}

#endif //__CLASSNAME__