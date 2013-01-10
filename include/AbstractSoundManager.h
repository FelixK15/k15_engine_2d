#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include "StandardIncludes.h"

namespace K15_Engine
{
	typedef std::list<SoundPtr> SoundList;

	class K15ENGINE_API AbstractSoundManager
	{

	public:

		virtual SoundPtr createSound() = 0;

		virtual SoundPtr createSound(Resource *resource) = 0;

		virtual SoundPtr createSound(const String& resourceName) = 0;

	protected:

		void _addToSoundCache(SoundPtr sound) { m_soundList.push_back(sound); }

		SoundList m_soundList;

		int m_soundVolume;
	};
}

#endif // __SOUNDMANAGER__
