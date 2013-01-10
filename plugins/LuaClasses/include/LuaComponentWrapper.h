#ifndef __LUA_COMPONENT_WRAPPER__
#define __LUA_COMPONENT_WRAPPER__

#include "LuaAble.h"

namespace K15_Engine
{
	class AbstractComponent;

	class LuaComponentWrapper : public LuaAble<LuaComponentWrapper>
	{
	public:
		LuaComponentWrapper(AbstractComponent *component);

		~LuaComponentWrapper();

		AbstractComponent *getComponent();

		int getParent(lua_State *state);

		static LuaAble<LuaComponentWrapper>::LuaCFunction m_functions[];

	private:
		AbstractComponent *m_component;
	};
}

#endif // __LUA_COMPONENT_WRAPPER__