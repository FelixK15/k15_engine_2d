#include "Globals.h"

using namespace K15_Engine;

//Screen Settings
bool K15_Engine::_FULLSCREEN = false;
int K15_Engine::_SCREENWIDTH = 800;
int K15_Engine::_SCREENHEIGHT = 600;
int K15_Engine::_BPP = 32;
int K15_Engine::_FPS = 30;
int K15_Engine::_START_CAMERAS = 1;
bool K15_Engine::_CAMERA_ALIGNMENT_HORIZONTAL = false;
bool K15_Engine::_ANTI_ALIASING = false;
char* K15_Engine::_SCREENCAPTION = "K15 Engine Game";
char* K15_Engine::_SCREENICON = "icon.png";

//Console Settings
char* K15_Engine::_CONSOLE_FONT = "font.ttf";
int K15_Engine::_CONSOLE_BACKGROUND_COLOR[4]  = {0,0,0,0};
int K15_Engine::_CONSOLE_FONT_COLOR[4]  = {255,255,255,128};

//Process Settings
bool K15_Engine::_MULTITHREADED_INPUTHANDLING = false;
bool K15_Engine::_MULTITHREADED_EVENTMESSAGING = false;

int K15_Engine::_AMOUNT_STARTUP_LUA_SCRIPTS = 0;
int K15_Engine::_AMOUNT_SHUTDOWN_LUA_SCRIPTS = 0;
char* K15_Engine::_STARTUP_LUA_SCRIPTS[20] = {};
char* K15_Engine::_SHUTDOWN_LUA_SCRIPTS[20] = {};

char* K15_Engine::_ENGINE_SUBSYSTEM = "Engine_SubSystem";

//Resource Settings
char* K15_Engine::_RESOURCEFILE = "resourcepak.kpk";
int K15_Engine::_SIZE_RESOURCE_CACHE = 52428800;
