#pragma once

#ifndef __LOGENTRY__
#define __LOGENTRY__

#include "StandardIncludes.h"
#include "DateTime.h"

namespace K15_Engine
{
	typedef enum MessagePriority{
		kDebug = 0,
		kNormal,
		kLua,
		kError,
		kCritical	
	}MessagePriority;
	
	class K15ENGINE_API LogEntry
	{
	public:
	
		LogEntry(const String & message,const MessagePriority priority);

		LogEntry(const LogEntry &logentry);
	
		MessagePriority getPriority();

		void setDateTime(DateTime dateTime);
	
		const String getMessage() const;

		const String &getShortMessage() const;

		LogEntry &operator=(const LogEntry& logentry){
			m_dateTime = logentry.m_dateTime;
			m_message = logentry.m_message;
			m_priority = logentry.m_priority;

			return *this;
		}
	
	private:
		DateTime m_dateTime;
		String m_message;
		MessagePriority m_priority;
	};
}

#endif //__LOGENTRY__