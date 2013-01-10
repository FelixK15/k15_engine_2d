#pragma once

#ifndef __FILEHANDLE__
#define __FILEHANDLE__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API FileHandle
	{
	
	friend class WindowsFileSubSystem;
	
	public:
		FileHandle();
	
		~FileHandle();
	
		byte *getData();
	
		U32 getSize();
	
		String getName();
	
		bool shouldDeleteAutomaticly();
	
		void dontDeleteAutomaticly();
	
	private:
		U32 m_size;
		byte *m_data;
		bool m_autoDelete;
		String m_name;
	};
}

#endif //__FILEHANDLE__