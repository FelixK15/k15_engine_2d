#ifndef __MUSICMANAGER__
#define __MUSICMANAGER__

#include "StandardIncludes.h"
#include "Log.h"

namespace K15_Engine
{
	typedef std::list<MusicPtr> MusicList;
	
	class IMusicManagerSubSystem;
	class Resource;

	class K15ENGINE_API AbstractMusicManager
	{

	public:

		virtual bool initialize() = 0;
		
		virtual void shutdown() = 0;

		virtual MusicPtr createMusic() = 0;

		virtual MusicPtr createMusic(Resource *resource) = 0;

		virtual MusicPtr createMusic(const String& resourceName) = 0;

	protected:

		void _addToMusicCache(MusicPtr music){ m_musicList.push_back(music); }

		MusicList m_musicList;

		int m_musicVolume;
	};
}


#endif // __MUSICMANAGER__
