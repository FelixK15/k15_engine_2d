#ifndef __LUA__MAKROS__
#define __LUA__MAKROS__

#define LUA_PUSH_POSITION(state,x,y)		lua_newtable(state);		\
											lua_pushstring(state,"y");	\
											lua_pushinteger(state,y);	\
											lua_settable(state,-3);		\
											lua_pushstring(state,"x");	\
											lua_pushinteger(state,x);	\
											lua_settable(state,-3);		

#define LUA_PUSH_SIZE(state,w,h)			lua_newtable(state);		\
											lua_pushstring(state,"h");	\
											lua_pushinteger(state,h);	\
											lua_settable(state,-3);		\
											lua_pushstring(state,"w");	\
											lua_pushinteger(state,w);	\
											lua_settable(state,-3);

#define LUA_PUSH_COLOR(state,r,g,b,a)		lua_newtable(state);		\
											lua_pushstring(state,"r");	\
											lua_pushinteger(state,r);	\
											lua_settable(state,-3);		\
											lua_pushstring(state,"g");	\
											lua_pushinteger(state,g);	\
											lua_settable(state,-3);		\
											lua_pushstring(state,"b");	\
											lua_pushinteger(state,b);	\
											lua_settable(state,-3);		\
											lua_pushstring(state,"a");	\
											lua_pushinteger(state,a);	\
											lua_settable(state,-3);		

#define LUA_PUSH_VARIANT(state,variant)		if(variant.type == TYPE_BOOL){							\
												lua_pushboolean(state,TO_C_BOOL(variant.toBool));	\
											}else if(variant.type == TYPE_FLOAT){					\
												lua_pushnumber(state,variant.toFloat);				\
											}else if(variant.type == TYPE_INTEGER){					\
												lua_pushnumber(state,variant.toInteger);			\
											}else if(variant.type == TYPE_STRING){					\
												lua_pushstring(state,variant.toString);				\
											}else if(variant.type == TYPE_DOUBLE){					\
												lua_pushnumber(state,variant.toDouble);				\
											}else{lua_pushnil(state);}				
											

#define TO_CPP_BOOL(val) val == 1 ? true : false

#define TO_C_BOOL(val) val ? 1 : 0

#define GET_OBJECT_TABLE(state)			lua_rawgeti(state,LUA_REGISTRYINDEX,getReference())

#define PUSH_NIL_VALUE(state,name)	lua_pushstring(state,name); \
										lua_pushnil(state);			\
										lua_settable(state,-3)

#define REMOVE_OBJECT_TABLE(state)		lua_pop(state,1)

#define GET_OBJECT_VALUE(state,val)		lua_pushstring(state,val); lua_gettable(state,-2);

#define TRY_TO_CALL_FUNCTION(state,numArguments,numReturns)			if(lua_pcall(state,numArguments,numReturns,0) != 0){	\
																		LUA_PRINT_ERROR(LUA_GET_STRING(-1));				\
																	}														\
																

#define END_LUA_C_FUNCTION() {0,0}

#define DO_IF_IS_FUNCTION(state,functionname)	GET_OBJECT_VALUE(state,functionname);																\
													if(!lua_isnil(state,-1) && !lua_isfunction(state,-1)){											\
														lua_pop(state,lua_gettop(m_state) - 1);															\
														LUA_PRINT_ERROR("Tried to call function \"" + String(functionname) + "\" but that's no function.");		\
														lua_error(state);																				\
													}else

#define TRY_TO_GET_THIS_POINTER(state,posOfTable)	lua_pushinteger(state,0); lua_gettable(state,posOfTable);

#define TRY_TO_GET_TABLE_DATATYPE(state,posOfTable) lua_pushstring(state,"DATATYPE"); lua_gettable(state,posOfTable);

#endif //__LUA__MAKROS__