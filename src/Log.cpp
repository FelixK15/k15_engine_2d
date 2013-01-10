#include "Log.h"
#include "DateTime.h"
#include "EventManager.h"
#include "Events.h"
#include <assert.h>
#include <time.h>

using namespace K15_Engine;

LogEntry Log::m_lastMessage = LogEntry("",kNormal);
std::ofstream Log::m_fileStream;

void Log::writeLog( const String &message,MessagePriority priority )
{
	if(priority == kCritical){
		assert(true);
	}
	LogEntry newEntry(message,priority);
	m_lastMessage = newEntry;

	newEntry.setDateTime(DateTime());

	NEW_EVENT(Events::MessageLogged);
	EXECUTE_NEW_EVENT_IMMEDIATELY();
	
	m_fileStream << newEntry.getMessage() + "\n";
	m_fileStream.flush();
}

void Log::writeLog( const String &message)
{
	writeLog(message,kNormal);
}