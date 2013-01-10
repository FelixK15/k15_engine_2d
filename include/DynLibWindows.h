/********************************************************************
	created:	2011/11/21
	created:	21:11:2011   22:39
	filename: 	DynLibWindows.h
	author:		Felix Klinge
	
	purpose:	Implementation for loading dynamic libraries
				under Windows.
*********************************************************************/

#pragma once

#ifndef __DYNLIBWINDOWS__
#define __DYNLIBWINDOWS__

#include "IDynLibOSSpec.h"

namespace K15_Engine
{
	class K15ENGINE_API DynLibWindows
		: public IDynLibOSSpec
	{

	public:

		DynLibWindows(const String& name);

		~DynLibWindows();

		void * getProcAddress(const String& name ) const;

		bool hasBeenLoaded() const;

		const String& getName() const;

	private:
			
		const String m_name;

		void *m_libHandle;
	};

}

#endif //__DYNLIBWINDOWS__