#pragma once

#ifndef __SDL_FONTMANAGERSUBSYSTEM__
#define __SDL_FONTMANAGERSUBSYSTEM__

#include "StandardIncludes.h"
#include "AbstractFontManager.h"

namespace K15_Engine
{
	class SDL_FontManager : public AbstractFontManager
	{
	public:

		SDL_FontManager();

		virtual ~SDL_FontManager();

		virtual bool initialize();

		virtual void shutdown();

		virtual FontPtr createFont();

		virtual FontPtr createFont( Resource *resource, U8 size = 12 );

		virtual FontPtr createFont( const String &resourceName,U8 size = 12 );

	};
}

#endif //__SDL_FONTMANAGERSUBSYSTEM__