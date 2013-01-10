#pragma once

#ifndef __LUAMANAGER__
#define __LUAMANAGER__

#include "Singleton.h"

#include <map>
#include <functional>
#include <string>
#include <list>

extern "C"
{
#include "lua\lua.h"
#include "lua\lualib.h"
#include "lua\lauxlib.h"
};

#define LUA_PRINT_ERROR(msg) LuaManager::printError(msg)

#define LUA_GET_ERROR() LuaManager::getLuaError()

#define LUA_GET_STRING(npos) LuaManager::getString(npos)

#define LUA_GET_INTEGER(npos) LuaManager::getInteger(npos)

#define LUA_GET_DOUBLE(npos) LuaManager::getDouble(npos)

#define LUA_GET_BOOL(npos) LuaManager::getBool(npos)

#define LUA_GET_USERDATA(npos) LuaManager::getUserData(npos)

namespace K15_Engine
{
//	class LuaObject;

//	typedef std::list<LuaObject*> LuaObjectList;

	class K15ENGINE_API LuaManager
	{
	public:

		static bool initialize();

		static bool shutdown();

		static lua_State *getLuaState();

		static void registerObjects();

		static void printError(const std::string& errormsg);

		static std::string getLuaError();

		static void update();

		inline static std::string getString(int npos){
			std::string ret = lua_tostring(m_state,npos);
			lua_remove(m_state,npos);

			return ret;
		}

		inline static int getInteger(int npos){
			int ret = lua_tointeger(m_state,npos);
			lua_remove(m_state,npos);

			return ret;
		}

		inline static double getDouble(int npos){
			double ret = lua_tonumber(m_state,npos);
			lua_remove(m_state,npos);

			return ret;
		}

		inline static bool getBool(int npos){
			bool ret = lua_toboolean(m_state,npos) == 0;
			lua_remove(m_state,npos);

			return ret;
		}

		inline static void* getUserData(int npos){
			void* ret = lua_touserdata(m_state,npos);
			lua_remove(m_state,npos);

			return ret;
		}

// 		inline static void subscribeLuaObject(LuaObject *object){
// 			m_objectList.push_back(object);
// 		}

	private:

		static lua_State *m_state;

//		static LuaObjectList m_objectList;
	};
}

#endif //__LUAMANAGER__