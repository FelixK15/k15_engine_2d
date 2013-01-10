#pragma once

#ifndef	__ABSTRACTWINDOW__
#define	__ABSTRACTWINDOW__

#include "StandardIncludes.h"
#include "Size.h"

namespace K15_Engine
{
	class K15ENGINE_API AbstractWindow
	{
	public:

		virtual ~AbstractWindow();
		
		virtual bool create() = 0;
	
		virtual void destroy() = 0;
	
		virtual bool swapBuffers() = 0;
	
		virtual void setCaption(const String& caption) = 0;

		const Size& getSize(){return m_size;}

		void setFullScreen(bool fullscreen);
	
		bool isActive();
	
		bool isFullScreen();
	
		const String& getCaption();

		bool reCreate()
		{
			destroy();
			return create();
		}
	
	protected:
		AbstractWindow(int width,int height,int bpp,bool fullscreen,const String& caption)
		{
			m_size = Size(width,height);
			m_bpp = bpp;
			m_fullscreen = fullscreen;
			m_caption = caption;
		}

		String m_caption;
		Size m_size;
		U8 m_bpp;
		bool m_active,m_fullscreen;
	};
}

#endif //__ABSTRACTWINDOW__