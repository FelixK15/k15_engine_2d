#ifndef __FONTMANAGER__
#define __FONTMANAGER__

#include "Singleton.h"
#include "Resource.h"

namespace K15_Engine
{
	typedef std::list<FontPtr> FontList;

	class IFontManagerSubSystem;

	class K15ENGINE_API AbstractFontManager
	{

	public:

		AbstractFontManager();

		virtual ~AbstractFontManager();

		virtual bool initialize() = 0;

		virtual void shutdown() = 0;

		virtual FontPtr createFont() = 0;

		virtual FontPtr createFont(Resource *resource,U8 size = 12) = 0;

		virtual FontPtr createFont(const String &resourceName,U8 size = 12) = 0;

	protected:

		void _addToFontCache(FontPtr font) { m_fonts.push_back(font); }

		FontList m_fonts;

	};
}

#endif // __FONTMANAGER__
