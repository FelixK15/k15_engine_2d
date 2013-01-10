/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * 
 */
#pragma once

#ifndef __LUAABLE__
#define __LUAABLE__

#include "StandardIncludes.h"
#include "LuaManager.h"
#include "LuaObject.h"

#define toLuaCFunction(classname,func) {#func,&classname::func}

namespace K15_Engine
{
	template<class T> 
	class LuaAble : public LuaObject
	{
	
	public:

	typedef int (T::*callbackFunc)(lua_State*);

	struct LuaCFunction{
		const char* name;
		callbackFunc function;
	};

		LuaAble() : LuaObject(){
			registerObject();
		}

		virtual ~LuaAble(){
			unregisterObject();
		}

	private:

		static int callbackFunction(lua_State *state){
			int tableIndex = lua_tointeger(state,lua_upvalueindex(2));
			lua_rawgeti(state,LUA_REGISTRYINDEX,tableIndex);
			if(lua_istable(state,-1)){
				lua_pushinteger(state,0);
				lua_gettable(state,-2);

				if(lua_islightuserdata(state,-1)){
					T* pointer_this = static_cast<T*>(lua_touserdata(state,-1));

					lua_remove(state, -1);
					LuaCFunction* func = static_cast<LuaCFunction*>(lua_touserdata(state, lua_upvalueindex(1)));
					lua_remove (state, -1);

					return (pointer_this->*(func->function))(state);  // call member function
				}
			}

			return 0;
		}	
		
		void registerMethods(){
			lua_rawgeti(m_state,LUA_REGISTRYINDEX,getReference());

			if(lua_istable(m_state,-1)){

				for(LuaCFunction *curFunc = T::m_functions;curFunc->name;curFunc++){
					lua_pushstring(m_state,curFunc->name);
					lua_pushlightuserdata(m_state,curFunc);
					lua_pushinteger(m_state,m_tableIndex);
					lua_pushcclosure(m_state,callbackFunction,2);
					lua_settable(m_state,-3);
				}

// 				LuaCFunction deleter = {"__gc",&LuaObject::setDead};
// 
// 				lua_pushstring(m_state,"__gc");
// 				lua_pushlightuserdata(m_state,&deleter);
//  				lua_pushcclosure(m_state,callbackFunction,1);
//  				lua_settable(m_state,-3);
// 				luaL_newmetatable(m_state,"LuaObject");
// 
// 				LuaCFunction deleter = {"__gc",&LuaObject::setDead};
// 
// 				lua_pushstring(m_state,"__gc");
// 				lua_pushlightuserdata(m_state,&deleter);
//  				lua_pushcclosure(m_state,callbackFunction,1);
//  				lua_settable(m_state,-3);
// 
// 				lua_setmetatable(m_state,-2);

				lua_pop(m_state,1);
			}
		}

		void registerObject(){
			m_state = LuaManager::getLuaState();
			
			lua_newtable(m_state);
			m_tableIndex = luaL_ref(m_state,LUA_REGISTRYINDEX);
			m_tableIndex = luaL_ref(m_state,LUA_REGISTRYINDEX);
			setReference(luaL_ref(m_state,LUA_REGISTRYINDEX));

			lua_rawgeti (m_state, LUA_REGISTRYINDEX, m_tableIndex);
			lua_rawgeti (m_state, LUA_REGISTRYINDEX, getReference());
			lua_pushlightuserdata (m_state, (void *)(static_cast<T*>(this)));
			lua_rawseti (m_state, -2, 0);

			registerMethods();
		}

		void unregisterObject(){
			if (m_state){
				luaL_unref(m_state,LUA_REGISTRYINDEX,m_tableIndex);
				luaL_unref(m_state,LUA_REGISTRYINDEX,getReference());
				m_state = NULL;
			}
		}

	protected:
		lua_State *m_state;
	};
}

#endif //__CLASSNAME__