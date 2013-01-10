#pragma once

#ifndef __GLOBALS__
#define __GLOBALS__

namespace K15_Engine
{
	//Screen Settings
	extern bool _FULLSCREEN;
	extern int _SCREENWIDTH;
	extern int _SCREENHEIGHT;
	extern int _BPP;
	extern int _FPS;
	extern int _START_CAMERAS;
	extern bool _CAMERA_ALIGNMENT_HORIZONTAL;
	extern bool _ANTI_ALIASING;
	extern char *_SCREENCAPTION;
	extern char *_SCREENICON;

	//Console Settings
	extern char *_CONSOLE_FONT;
	extern int _CONSOLE_BACKGROUND_COLOR[];
	extern int _CONSOLE_FONT_COLOR[];

	//Process Settings
	extern bool _MULTITHREADED_INPUTHANDLING;
	extern bool _MULTITHREADED_EVENTMESSAGING;

	extern int _AMOUNT_STARTUP_LUA_SCRIPTS;
	extern int _AMOUNT_SHUTDOWN_LUA_SCRIPTS;
	extern char *_STARTUP_LUA_SCRIPTS[];
	extern char *_SHUTDOWN_LUA_SCRIPTS[];

	extern char *_ENGINE_SUBSYSTEM;
	
	//Resource Settings
	extern char *_RESOURCEFILE;
	extern int _SIZE_RESOURCE_CACHE;
}

#endif //__GLOBALS__