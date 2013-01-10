/********************************************************************
	created:	2011/12/30
	created:	30:12:2011   2:58
	filename: 	ConfigFile.h
	author:		Felix Klinge
	
	purpose:	
*********************************************************************/

#pragma once

#ifndef __CONFIGFILE__
#define __CONFIGFILE__

#include "StandardIncludes.h"
#include "Variant.h"

namespace K15_Engine
{

#define GET_N_CONFIG_VALUE(n,map,expr) map[expr].values.at(n)
#define GET_CONFIG_VALUE(map,expr) map[expr].values

	struct ConfigEntry
	{
		String name;
		String group;
		std::vector<Variant> values;
	};

	typedef std::map<String,ConfigEntry> ConfigEntryMap;

	class K15ENGINE_API ConfigFile
	{
	public:

		static void loadConfigFile();

		static ConfigEntry getValue(const String& name);

		static ConfigEntryMap getValues(const String& groupName);

	};
}

#endif //__CLASSNAME__