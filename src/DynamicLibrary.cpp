#include "DynamicLibrary.h"

#ifdef _WIN32
	#include "DynLibWindows.h"
#endif

using namespace K15_Engine;


DynamicLibrary::DynamicLibrary( const String& file )
{
	#ifdef _WIN32
		m_dynLib = new DynLibWindows(file);
	#endif
}

DynamicLibrary::~DynamicLibrary()
{
	delete m_dynLib;
}

void * DynamicLibrary::getFunction( const String& functionName ) const
{
	return m_dynLib->getProcAddress(functionName);
}

bool DynamicLibrary::hasBeenLoaded() const
{
	return m_dynLib->hasBeenLoaded();
}

String const DynamicLibrary::getName() const
{
	return m_dynLib->getName();
}
