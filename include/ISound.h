#pragma once

#ifndef __ISOUND__
#define __ISOUND__

#include "DLL_Header.h"
#include "IResourceable.h"

namespace K15_Engine
{
	class K15ENGINE_API ISound : public IResourceable
	{

	public:

		virtual bool play() = 0;

		virtual bool play(int times) = 0;

		virtual void stop() = 0;

		virtual bool setContent(Resource *resource) = 0;

		virtual bool loadedSuccessful() = 0;

		virtual bool copyFrom(IResourceable *resourceable) = 0;
	};
}

#endif //__ISOUND__
