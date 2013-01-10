#pragma once

#ifndef __STANDARDINCLUDE__
#define __STANDARDINCLUDE__

//Standard includes.
#include <string>
#include <vector>
#include <bitset>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <utility>
#include <deque>
#include <list>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <memory>
#include <cassert>
#include <functional>
#include <time.h>


//Forward Declarations
namespace K15_Engine{
	class Game;

	class IFont;
	class IGraphic;
	class IMusic;
	class ISound;
	class IEngineSubSystem;
	class IEventListener;

	class Color;
	class Log;
	class Rectangle;
	class Line;
	class Resource;
	class IResourceable;
	class GameObject;
	class Size;
	class Position;
	class Camera;
	class GameWorld;
	class GameWorldLayer;
	class Resource;

	class AbstractGraphicManager;
	class AbstractSoundManager;
	class AbstractFontManager;
	class AbstractMessageQueue;
	class AbstractMusicManager;
	class AbstractSystemManager;
	class AbstractWindow;

	class StateMachine;
	class EventManager;
	class ResourceManager;
	class Console;
}

//Typedefs
typedef unsigned char byte;
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned int U32;
typedef signed int S32;
typedef float F32;
typedef K15_Engine::Color Pixel;

#ifdef _UNICODE
typedef std::wstring String;
#else
typedef std::string String;
#endif

typedef std::fstream FileStream;
typedef std::ifstream InputFileStream;
typedef std::ofstream OutputFileStream;
typedef std::stringstream StringStream;

typedef std::tr1::shared_ptr<K15_Engine::IFont> FontPtr;
typedef std::tr1::shared_ptr<K15_Engine::IGraphic> GraphicPtr;
typedef std::tr1::shared_ptr<K15_Engine::IMusic> MusicPtr;
typedef std::tr1::shared_ptr<K15_Engine::ISound> SoundPtr;

#define SAFE_DELETE(ptr) if(ptr != NULL) \
						 {delete ptr;\
						 ptr = NULL;}

#include "DLL_Header.h"

#pragma warning(disable:4251)

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

template<typename T>
void Deleter(T obj){
	SAFE_DELETE(obj);
}

#ifdef _MSC_VER
	#ifdef NULL
		#undef NULL
		#define NULL nullptr
	#endif
#endif

//Custom includes.
#include "Globals.h"
#include "Keymap.h"
#include "UsefulMakros.h"
#include "ComponentFactory.h"

// #include "Debug.h"
// #include "StringConverter.h"
// #include "GameObjectManager.h"
// #include "Log.h"
// #include "GraphicManager.h"
// #include "ResourceManager.h"
// #include "TimerManager.h"
// #include "IGraphic.h"
// #include "IFont.h"


#endif //__STANDARDINCLUDE__


