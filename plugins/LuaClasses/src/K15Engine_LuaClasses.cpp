#include "K15Engine_LuaClasses.h"

#include <string>
#include <algorithm>

#include "Game.h"
#include "StringConverter.h"
#include "ComponentFactory.h"

#include "Makros.h"
#include "Log.h"

#include "LuaGameObject.h"
#include "LuaGraphic.h"
#include "LuaFont.h"
#include "LuaGameWorldLayer.h"
#include "LuaGameWorld.h"
#include "LuaState.h"
#include "LuaEventListener.h"
#include "LuaComponent.h"
#include "LuaComponentWrapper.h"
#include "LuaEvent.h"

extern "C"
{
#include "lua\lua.h"
#include "lua\lauxlib.h"
#include "lua\lualib.h"
};

using namespace K15_Engine;

#define HAS_SECOND_ARGUMENT() lua_isstring(state,1)

#define NORMAL_CONSTRUCT(constr) new constr()

#define ARGUMENT_CONSTRUCT(constr) new constr(LUA_GET_STRING(1))

#define CONSTRUCT_OBJECT_WITH_SECOND_ARG(obj)		if(HAS_SECOND_ARGUMENT()){		\
														ARGUMENT_CONSTRUCT(obj);	\
													}else{							\
														NORMAL_CONSTRUCT(obj);		\
													}

#define LUA_C_FUNCTION(name,func) {name,func}

//forward declaration.
AbstractComponent *componentCreatorFunction(VariantList paramList);

int setState(lua_State *state);

int getCurrentTick(lua_State *state);

int addComponentCreator(lua_State *state);

int createComponent(lua_State *state);

int draw(lua_State *state);

int logMessage(lua_State *state);

///////////////////////////////////

void createLuaGameObject(lua_State *state);

void createLuaGraphic(lua_State *state);

void createLuaEvent(lua_State *state);

void createLuaFont(lua_State *state);

void createLuaEventListener(lua_State *state);

void createLuaComponent(lua_State *state);

void createLuaState(lua_State *state);

void createLuaGameWorld(lua_State *state);

void createLuaGameWorldLayer(lua_State *state);

///////////////////////////////////

int luaopen_K15Engine_LuaClasses(lua_State *state)
{
	const struct luaL_Reg k15LuaLib[] = {
		LUA_C_FUNCTION("create",newFunc),
		LUA_C_FUNCTION("setState",setState),
		LUA_C_FUNCTION("getCurrentTick",getCurrentTick),
		LUA_C_FUNCTION("addComponentCreator",addComponentCreator),
		LUA_C_FUNCTION("createComponent", createComponent),
		LUA_C_FUNCTION("draw",draw),
		LUA_C_FUNCTION("logMessage",logMessage),
		END_LUA_C_FUNCTION()
	};

	luaL_register(state,"K15Engine",k15LuaLib);

	return 1;
}

int newFunc(lua_State *state)
{
	if(lua_isstring(state,1)){
		std::string type = LUA_GET_STRING(1);
		std::transform(type.begin(),type.end(),type.begin(),tolower);

		if(type == "gameobject"){
			createLuaGameObject(state);
		}else if(type == "graphic"){
			createLuaGraphic(state);
		}else if(type == "font"){
			createLuaFont(state);
		}else if(type == "gameworld"){
			createLuaGameWorld(state);
		}else if(type == "gameworldlayer"){
			createLuaGameWorldLayer(state);
		}else if(type == "state"){
			createLuaState(state);
		}else if(type == "event"){
			createLuaEvent(state);
		}else if(type == "eventlistener"){
			createLuaEventListener(state);
		}else if(type == "component"){
			if(HAS_SECOND_ARGUMENT()){
				createLuaComponent(state);
			}else{
				LUA_PRINT_ERROR("Component construction need 2 arguments | K15Engine.create(\"component\",\"TYPE\").");
				lua_pushnil(state);
			}
			
		}else{
			LUA_PRINT_ERROR("Couldn't create engine object \"" + type + "\"");
			lua_pushnil(state);
		}

		//If a table got created the type of the table will be pushed into the table for later recognition
		if(lua_istable(state,-1)){
			lua_pushstring(state,"DATATYPE");
			lua_pushstring(state,type.c_str());
			lua_settable(state,-3);
		}

	}else{
		LUA_PRINT_ERROR("Expected first argument to be from type \"string\".");
		lua_pushnil(state);
	}

	return 1;
}

int setState(lua_State *state)
{
	bool ret = false;

	if(lua_istable(state,-1)){
		lua_pushnumber(state,0);
		lua_gettable(state,-2);

		if(lua_islightuserdata(state,-1)){
			LuaState *luaState = static_cast<LuaState*>(lua_touserdata(state,-1));

			myGame->getStateMachine()->setNextState(luaState);
			ret = true;
		}

		lua_pop(state,1);
	}

	if(!ret){
		LUA_PRINT_ERROR("Expected argument of type \"State\".");
	}

	lua_pushboolean(state,TO_C_BOOL(ret));
	return 1;
}

int getCurrentTick(lua_State *state)
{
	U32 currentTick = myGame->getSystemManager()->getTick();

	lua_pushnumber(state,currentTick);

	return 1;
}

int addComponentCreator(lua_State *state)
{
	//Check if enough arguments have been passed.
	if(lua_gettop(state) < 3){
		LUA_PRINT_ERROR("Passed to few arguments. (3 arguments expected | string : typename,function : create function for the component,int amount of arguments that the create function expects.)");
		lua_pushboolean(state,TO_C_BOOL(false));

		return 1;
	}

	//Check if the arguments are of the right type.
	if(!(lua_isstring(state,-3) && lua_isnumber(state,-2) && lua_isfunction(state,-1))){
		LUA_PRINT_ERROR("Expected 1st argument to be a string, 2nd argument to be a function and 3rd argument to be a number.");
		lua_pushboolean(state,TO_C_BOOL(false));

		return 1;
	}

	
	String type = LUA_GET_STRING(1);
	String creationTableName = "creation_table_" + type;
	
	//saves the number of arguments the creation function needs.
	int numArgs = LUA_GET_INTEGER(1);

	//create a reference to the creation function
	int functionIndex = luaL_ref(state,LUA_REGISTRYINDEX);

	//Creates a new table where all necessary informations will get saved (a bit complicated)
	lua_newtable(state);
	//Table gets saved as new global table with the name "creation_table_TYPE" (table will get popped in the process)
	lua_setglobal(state,creationTableName.c_str());

	//pushes the table back to the stack.
	lua_getglobal(state,creationTableName.c_str());

	//push new field "function_index" and its value.
	lua_pushstring(state,"function_index");
	lua_pushinteger(state,functionIndex);
	lua_settable(state,-3);

	//push new field "function_argument_number" and its value.
	lua_pushstring(state,"function_argument_number");
	lua_pushinteger(state,numArgs);
	lua_settable(state,-3);

	//pop the table from the stack.
	lua_pop(state,1);

	bool result = ComponentFactory::addComponentCreator(type,componentCreatorFunction);

	lua_pushboolean(state,TO_C_BOOL(result));

	return 1;
}

int createComponent(lua_State *state)
{
	if(lua_gettop(state) < 1){
		LUA_PRINT_ERROR("Too few arguments where passed to function \"createComponent\".");
		lua_pushnil(state);

		return 1;
	}

	int numArguments = lua_gettop(state) - 1;
	String type = LUA_GET_STRING(1);
	
	VariantList varList;

	int counter = 0;
	while(numArguments-- > 0){
		++counter;
		int luaType = lua_type(state,1);
		if(luaType == LUA_TSTRING){
			String stringArgument = LUA_GET_STRING(1);
			varList.push_back(Variant(stringArgument));
		}else if(luaType == LUA_TNUMBER){
			double number = LUA_GET_DOUBLE(1);
			varList.push_back(Variant(number));
		}else if(luaType == LUA_TBOOLEAN){
			bool value = TO_CPP_BOOL(LUA_GET_BOOL(1));
			varList.push_back(Variant(value));
		}else if(luaType == LUA_TTABLE){
			TRY_TO_GET_TABLE_DATATYPE(state,1);
			
			//Check if datatype has been added to the stack.
			if(lua_isstring(state,-1)){
				//Get datatype.
				String dataType = LUA_GET_STRING(-1);
				TRY_TO_GET_THIS_POINTER(state,1);

				//Check if the this pointer has been added to the stack.
				if(lua_islightuserdata(state,-1)){

					//check for the correct datatype and cast it to add it to the parameter list.
					if(dataType == "graphic"){
						LuaGraphic *luaGraphic = static_cast<LuaGraphic*>(LUA_GET_USERDATA(-1));
						varList.push_back(Variant(luaGraphic->getGraphic()));
					}else if(dataType == "font"){
						LuaFont *luaFont = static_cast<LuaFont*>(LUA_GET_USERDATA(-1));
						varList.push_back(Variant(luaFont->getFont()));
					}else if(dataType == "music"){

					}else if(dataType == "sound"){

					}else{
						//dataType could not be identified.
						LUA_PRINT_ERROR("Undefined datatype \"" + dataType + "\".");
						if(!lua_isnoneornil(state,-1)){
							lua_remove(state,-1);
						}
					}
				}

			}

		}else{
			String luaType = lua_typename(state,1);
			LUA_PRINT_ERROR("Couldn't analyse " + StringConverter::toString(counter) + ". argument of type \"" + luaType + "\".");
			lua_remove(state,1);
		}
	}

	AbstractComponent *component = ComponentFactory::create(type,varList);

	if(component == NULL){
		LUA_PRINT_ERROR("There's no component with the name \"" + type + "\" to create.");
		lua_pushnil(state);

		return 1;
	}

	new LuaComponentWrapper(component);

	return 1;
}

AbstractComponent *componentCreatorFunction(VariantList paramList)
{
	lua_State *state = LuaManager::getLuaState();
	
	String type = paramList.begin()->toString;

	String creationTableName = "creation_table_" + type;

	//tries to get the creation table of this component.
	lua_getglobal(state,creationTableName.c_str());

	//did I found the table?
	if(!lua_istable(state,-1)){
		//no table was found. Erase whatever is left on the stack.
		while(lua_gettop(state)){
			lua_pop(state,1);
		}

		return NULL;
	}else{
		//found the table. Number of arguments and function index will get saved for later use.
		lua_pushstring(state,"function_argument_number");
		lua_gettable(state,-2);

		int argumentNumber = LUA_GET_INTEGER(-1);
	
		//Check if the size of the passed paramester is equal with the size of the arguments this function expects.
		if(paramList.size() != argumentNumber + 1){
			WRITE_ERRORLOG("Component creator function for type \"" + type +"\" expects " + StringConverter::toString(argumentNumber) + " arguments. Too few or too much arguments have been passed.");
			return NULL;
		}

		//Get the lua creation function.
		lua_pushstring(state,"function_index");
		lua_gettable(state,-2);

		//Save the function index.
		int function_index = LUA_GET_INTEGER(-1);

		//push the function on the stack.
		lua_rawgeti(state,LUA_REGISTRYINDEX,function_index);

		//Push each parameter from the parameter list to lua.
		for(VariantList::iterator i = ++paramList.begin();i != paramList.end();i++){
			Variant curParam = (*i);

			if(curParam.type == TYPE_BOOL){							
				lua_pushboolean(state,TO_C_BOOL(curParam.toBool));	
			}else if(curParam.type == TYPE_FLOAT){					
				lua_pushnumber(state,curParam.toFloat);				
			}else if(curParam.type == TYPE_INTEGER){					
				lua_pushnumber(state,curParam.toInteger);			
			}else if(curParam.type == TYPE_STRING){					
				lua_pushstring(state,curParam.toString);			
			}else if(curParam.type == TYPE_DOUBLE){					
				lua_pushnumber(state,curParam.toDouble);				
			}else if(curParam.type == TYPE_GRAPHIC){
				new LuaGraphic(curParam.toGraphic);
			}else if(curParam.type == TYPE_FONT){
				new LuaFont(curParam.toFont);
			}else if(curParam.type == TYPE_SOUND){

			}else if(curParam.type == TYPE_MUSIC){

			}else{
				lua_pushnil(state);
			}				
		}

		//Try to call the lua creation function.
		TRY_TO_CALL_FUNCTION(state,argumentNumber,1);

		//Check if the return type is wether nil or of an unsupported type.
		if(lua_isnil(state,-1) || !lua_istable(state,-1)){
			String returnType = lua_typename(state,-1);
			WRITE_ERRORLOG("Function didn't return a new component. (Type was \"" + returnType + "\".");
			lua_pop(state,1);

			return NULL;
		}else{
			//Get the "this pointer" of the table the lua function returned.
			lua_pushnumber(state,0);
			lua_gettable(state,-2);

			//Cast the this pointer to the Component type.
			LuaComponent *component = static_cast<LuaComponent*>(LUA_GET_USERDATA(-1));

			//Remove the table from the stack.
			REMOVE_OBJECT_TABLE(state);
			
			return component;
		}
	}
}

int draw(lua_State *state)
{
	if(lua_istable(state,1)){
		lua_pushinteger(state,0);
		lua_gettable(state,-2);

		LuaGraphic *graphic = static_cast<LuaGraphic*>(LUA_GET_USERDATA(-1));

		bool ret = myGame->getGraphicManager()->subscribeGraphic(graphic->getGraphic());

		lua_pop(state,1);

		lua_pushboolean(state,TO_C_BOOL(ret));
	}else{
		LUA_PRINT_ERROR("Expected argument of type \"K15Games.Graphic\".");
		lua_pushboolean(state,TO_C_BOOL(false));
	}

	return 1;
}

int logMessage(lua_State *state)
{
	String msg = LUA_GET_STRING(1);

	Log::writeLog(msg,kLua);

	return 0;
}

void createLuaGameObject(lua_State *state)
{
	if(lua_isstring(state,1)){
		String type = LUA_GET_STRING(1);
		new LuaGameObject(type);
	}else{
		new LuaGameObject("LuaGameObject");
	}
}

void createLuaGraphic(lua_State *state)
{
	if(lua_isstring(state,1)){
		String resource = LUA_GET_STRING(1);
		new LuaGraphic(resource);

		return;
	}else if(lua_istable(state,1)){
		TRY_TO_GET_THIS_POINTER(state,1);

		//Delete the table from the stack.
		lua_remove(state,1);

		if(lua_isuserdata(state,-1)){
			LuaGraphic *luaGraphic = static_cast<LuaGraphic*>(LUA_GET_USERDATA(-1));

			if(luaGraphic != NULL){
				GraphicPtr graphic = luaGraphic->getGraphic();

				new LuaGraphic(graphic);

				return;
			}
		}
	}

	lua_pushnil(state);
}

void createLuaEvent(lua_State *state)
{
	if(lua_isstring(state,1)){
		String eventType = LUA_GET_STRING(1);
		new LuaEvent(eventType);
	}else{
		new LuaEvent("undefined");
	}
}

void createLuaFont(lua_State *state)
{
	if(lua_isstring(state,1)){
		String resource = LUA_GET_STRING(1);
		new LuaFont(resource);

		return;
	}else if(lua_istable(state,1)){
		TRY_TO_GET_THIS_POINTER(state,1);

		//Delete the table from the stack.
		lua_remove(state,1);

		if(lua_isuserdata(state,-1)){
			LuaFont *luaFont = static_cast<LuaFont*>(LUA_GET_USERDATA(-1));

			if(luaFont != NULL){
				FontPtr font = luaFont->getFont();

				new LuaFont(font);
				return;
			}
		}

	}

	lua_pushnil(state);
}

void createLuaEventListener(lua_State *state)
{
	if(lua_isstring(state,1)){
		String eventType = LUA_GET_STRING(1);
		new LuaEventListener(eventType);

		return;
	}else if(lua_istable(state,1)){
		TRY_TO_GET_THIS_POINTER(state,1);

		//Delete the table from the stack.
		lua_remove(state,1);

		if(lua_isuserdata(state,-1)){
			LuaEvent *luaEvent = static_cast<LuaEvent*>(LUA_GET_USERDATA(-1));

			if(luaEvent != NULL){
				new LuaEventListener(luaEvent->getEvent().getType().getString());

				return;
			}
		}
	}

	lua_pushnil(state);
}

void createLuaComponent(lua_State *state)
{
	if(lua_isstring(state,1)){
		String type = LUA_GET_STRING(1);
		new LuaComponent(type);

		return;
	}

	lua_pushnil(state);
}

void createLuaState(lua_State *state)
{
	new LuaState();
}

void createLuaGameWorld(lua_State *state)
{
	if(lua_isstring(state,1)){
		String resource = LUA_GET_STRING(1);
		new LuaGameWorld(resource);

		return;
	}else if(lua_istable(state,1)){
		TRY_TO_GET_THIS_POINTER(state,1);
		lua_remove(state,1);

		if(lua_isuserdata(state,-1)){
			LuaGameWorld *luaGameWorld = static_cast<LuaGameWorld*>(LUA_GET_USERDATA(-1));

			if(luaGameWorld != NULL){
				new LuaGameWorld(luaGameWorld->getGameWorld());

				return;
			}
		}
	}

	lua_pushnil(state);
}

void createLuaGameWorldLayer(lua_State *state)
{
	if(lua_isstring(state,1)){
		String name = LUA_GET_STRING(1);
		new LuaGameWorldLayer(name);

		return;
	}else if(lua_istable(state,1)){
		TRY_TO_GET_THIS_POINTER(state,1);
		lua_remove(state,1);

		if(lua_isuserdata(state,-1)){
			LuaGameWorldLayer *luaGameWorldLayer = static_cast<LuaGameWorldLayer*>(LUA_GET_USERDATA(-1));

			if(luaGameWorldLayer != NULL){
				new LuaGameWorldLayer(luaGameWorldLayer->getGameWorldLayer());

				return;
			}
		}
	}

	new LuaGameWorldLayer("LuaGameWorldLayer");
}