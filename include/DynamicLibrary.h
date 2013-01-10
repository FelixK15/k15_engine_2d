/********************************************************************
	created:	2011/11/21
	created:	21:11:2011   22:22
	filename: 	DynamicLibrary.h
	author:		Felix Klinge
	
	purpose:	RAII Class for dynamic library loading.
				Nearly every call to functions will be 
				forwarded to the specific OS Implementation.
*********************************************************************/

#pragma once

#ifndef __DYNAMICLIBRARY__
#define __DYNAMICLIBRARY__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class IDynLibOSSpec;

	class K15ENGINE_API DynamicLibrary
	{
	public:

		//Constructor. Paramater = name of the dynamic library.
		DynamicLibrary(const String& file);

		~DynamicLibrary();
		
		//returns the address of the demanded function.
		void *getFunction(const String& functionName) const;

		//returns true if the library was loaded successful.
		//return false if not.
		bool hasBeenLoaded() const;

		//returns the name of the library.
		String const getName() const;

	private:

		IDynLibOSSpec *m_dynLib;
	};
}

#endif //__DYNAMICLIBRARY__