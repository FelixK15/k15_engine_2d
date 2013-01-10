#pragma once

#ifndef __STRINGCONVERTER__
#define __STRINGCONVERTER__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API StringConverter
	{
	public:
		static String toString(int val);
	
		static String toString(unsigned int val);

		static String toString(float val);
	
		static String toString(bool val);
	
		static int toInt(String val,int failValue = 0);
	
		static float toFloat(String val,float failValue = 0.0f);
	
		static bool toBool(String val,bool failValue = false);

		static int HexStringToInt(String val,int failValue = 0);
	};
}

#endif //__STRINGCONVERTER__