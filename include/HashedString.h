#pragma once

#ifndef __HASHEDSTRING__
#define __HASHEDSTRING__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API HashedString
	{
	
	friend class Event;
	
	public:
		explicit HashedString(const char * string);
	
		~HashedString();
	
		U32 getIdentifier() const;
	
		const char* getString();
	
		bool operator< (HashedString const &otherString) const;
	
		bool operator== (HashedString const &otherString);
	
		static void * createIdentifier(const char *string);
	
	private:
		void *m_identifier;
	
		String m_string;
	};
}

#endif //__HASHEDSTRING__