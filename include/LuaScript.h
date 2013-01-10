#pragma once

#ifndef __LUASCRIPT__
#define __LUASCRIPT__

#include "StandardIncludes.h"
#include "Variant.h"

namespace K15_Engine
{
	typedef std::list<Variant> ArgumentList;
	typedef Variant ReturnValue;

	class K15ENGINE_API LuaScript
	{

	public:

		LuaScript(const String& scriptFile);

		~LuaScript();

		bool execute();

		bool execute(const String& functionName);

		bool execute(const String& functionName,ArgumentList *arguments);

		ReturnValue getReturnValue();

	private:

		bool _loadScriptFile();

		ReturnValue m_returnVal;

		const String m_scriptFile;

		bool m_scriptFileLoaded;
		
	};
}

#endif //__CLASSNAME__