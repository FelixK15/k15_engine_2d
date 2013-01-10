#ifndef __K15_LUACLASSES__
#define __K15_LUACLASSES__

#include "LuaGameObject.h"
#include "LuaGraphic.h"

struct lua_State;

int luaopen_K15Engine_LuaClasses(lua_State *state);

int newFunc(lua_State *state);
#endif