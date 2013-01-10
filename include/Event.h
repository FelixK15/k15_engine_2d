#pragma once

#ifndef __K15_EVENT__
#define __K15_EVENT__

#include "StandardIncludes.h"
#include "HashedString.h"
#include "Variant.h"

namespace K15_Engine
{
	typedef std::map<String,Variant> EventArguments;
	typedef HashedString EventType;
	
	class K15ENGINE_API Event
	{
	public:
		
		Event(const String &identifier);

		Event(EventType identifier);

		Event(const Event& otherEvent);
	
		~Event();
	
		EventType getType() const;
		
		Variant getArgument(String const &argument) const;
	
		Variant getArgument(const char* argument) const;
	
		void setArgument(String const &argument,Variant &value);
	
		void setArgument(const char* argument,Variant &value);
	
		bool operator <(const Event & otherEvent) const;
	
		bool operator ==(const Event & otherEvent) const;
		
	private:
		EventArguments m_arguments;
		EventType m_type;
	};
}

#endif //__K15_EVENT__