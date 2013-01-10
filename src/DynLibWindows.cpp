#include "DynLibWindows.h"
#include "Log.h"
#include <windows.h>

using namespace K15_Engine;

DynLibWindows::DynLibWindows( const String& name )
	: m_name(name + ".dll")
{
	m_libHandle = static_cast<void*>(LoadLibrary(name.c_str()));

	if(m_libHandle == NULL){
		WRITE_ERRORLOG("Library \"" + name + "\" could not be loaded.");
	}else{
		WRITE_DEBUG("Library \"" + name + "\" was loaded successful.");
	}
}

DynLibWindows::~DynLibWindows()
{
	if(m_libHandle != NULL){
		if(FreeLibrary(static_cast<HMODULE>(m_libHandle)) == TRUE){
			WRITE_DEBUG("Library \"" + m_name + "\" has been successfully unloaded.");
		}else{
			WRITE_ERRORLOG("Library \"" + m_name + "\" could not get unloaded.");
		}
	}
}

void * DynLibWindows::getProcAddress( const String& name ) const
{
	if(m_libHandle != NULL){
		return GetProcAddress(static_cast<HMODULE>(m_libHandle),name.c_str());
	}else{
		WRITE_ERRORLOG("Function \"" + name + "\" could not be loaded because the library \"" + m_name + "\" was not loaded successful.");
		return NULL;
	}

}

bool DynLibWindows::hasBeenLoaded() const
{
	return m_libHandle != NULL;
}

const String& DynLibWindows::getName() const
{
	return m_name;
}

