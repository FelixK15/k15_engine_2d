#pragma once

#ifndef __LOG__
#define __LOG__

#include "LogEntry.h"
#include "StringConverter.h"

namespace K15_Engine
{
#define WRITE_LOG(msg) Log::writeLog(String(msg))
#define WRITE_ERRORLOG(msg) Log::writeLog(String(msg) +"\n\t\tFunction:" + String(__FUNCTION__) + "\n\t\tFile: " + String(__FILE__) + "\n\t\tLine:" + StringConverter::toString(__LINE__),kError)
#define WRITE_CRITICALLOG(msg) Log::writeLog(String(msg) + "\n\t\tFunction:" + String(__FUNCTION__) + "\n\t\tFile:" + String(__FILE__) + "\n\t\tLine:" + StringConverter::toString(__LINE__),kCritical)
#define WRITE_DEBUG(msg) Log::writeLog(String(msg),kDebug)
#define WRITE_LUA(msg) Log::writeLog(String(msg),kLua)
	
	class K15ENGINE_API Log
	{
	public:

		static bool initialize(){
			m_fileStream.open("Log.txt",std::ios_base::trunc);
			return m_fileStream.is_open();
		}

		static bool shutdown(){
			if(m_fileStream.is_open()){
				m_fileStream.close();
				return true;
			}else{
				return false;
			}	
		}
	
		static void writeLog(const String &message,MessagePriority priority);
	
		static void writeLog(const String &message);

		static LogEntry getLatestEntry(){return m_lastMessage;}
	
	private:
		static LogEntry m_lastMessage;
		static std::ofstream m_fileStream;
	};
}

#endif //__LOG__