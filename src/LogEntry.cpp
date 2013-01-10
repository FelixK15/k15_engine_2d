#include "LogEntry.h"

using namespace K15_Engine;

LogEntry::LogEntry(const String & message,const MessagePriority priority )
	: m_message(message),
	m_priority(priority)
{

}

K15_Engine::LogEntry::LogEntry( const LogEntry &logentry )
	: m_message(logentry.m_message),
	  m_dateTime(logentry.m_dateTime),
	  m_priority(logentry.m_priority)
{

}

void LogEntry::setDateTime(DateTime dateTime)
{
	this->m_dateTime = dateTime;
}

MessagePriority LogEntry::getPriority()
{
	return m_priority;
}

const String LogEntry::getMessage() const
{
	switch(m_priority){
		case kError:
			return "[" + m_dateTime.toShortDateString() + "] [ERROR] " + m_message;
			break;

		case kDebug:
			return "[" + m_dateTime.toShortDateString() + "] [DEBUG] " + m_message;
			break;

		case kCritical:
			return "[" + m_dateTime.toShortDateString() + "] [CRITICAL] " + m_message;
			break;

		case kLua:
			return "[" + m_dateTime.toShortDateString() + "] [LUA] " + m_message;
			break;

		default:
			return "[" + m_dateTime.toShortDateString() + "] " + m_message;
	}
}

const String &LogEntry::getShortMessage() const
{
	return m_message;
}