#pragma once

#ifndef __IMUSIC__
#define __IMUSIC__

#include "DLL_Header.h"
#include "IResourceable.h"

namespace K15_Engine
{
	class K15ENGINE_API IMusic : public IResourceable
	{

	public:

		virtual ~IMusic(){};

		virtual void pause() = 0;

		virtual bool isRunning() = 0;

		virtual bool start(int loops) = 0;

		virtual bool start(int loops, int ms) = 0;

		virtual void stop() = 0;

		virtual void stop(int ms) = 0;

		virtual bool setContent(Resource *resource) = 0;

		virtual bool loadedSuccessful() = 0;

		virtual bool copyFrom(IResourceable *resourceable) = 0;
	};
}


#endif // __IMUSIC__
