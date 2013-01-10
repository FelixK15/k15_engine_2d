#ifndef __LUA_COMPONENT__
#define __LUA_COMPONENT__

#include "LuaAble.h"
#include "AbstractComponent.h"

namespace K15_Engine
{
	class LuaComponent : public LuaAble<LuaComponent>, public AbstractComponent
	{
	public:

		LuaComponent(const String& type);

		virtual ~LuaComponent(){}

		int getParent(lua_State *state);

		virtual void setDebugMode(bool val) override;

		virtual AbstractComponent *clone() override;

		virtual bool handleMessage(const Event &gameEvent) override;

		virtual void start() override;

		virtual void setSize(const Size& size) override;

		virtual void setPosition(const Position& position) override;

		virtual void setAngle(S16 angle) override;

		virtual void shutdown() override;

		virtual void update(U32 gameTime) override;

		static LuaAble<LuaComponent>::LuaCFunction m_functions[];

	};
}

#endif //__LUA_COMPONENT__