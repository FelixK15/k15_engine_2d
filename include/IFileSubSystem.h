#pragma once

#ifndef __IFILESUBSYSTEM__
#define __IFILESUBSYSTEM__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class FileHandle;
	class Log;
	
	class K15ENGINE_API IFileSubSystem
	{
	public:
	
		virtual std::vector<String> getFilesFromDirectory(String &directory) = 0;
	
		virtual bool createFile(const byte *content,String &filePath) = 0;
	
		virtual bool directoryExist(String &filePath) = 0;
	
		virtual bool fileExist(String &filePath) = 0;
	
		virtual bool createDirectory(String &folderName,String &path) = 0;
	
		virtual FileHandle *openFile(String &filePath) = 0;

	};
}

#endif //__IFILESUBSYSTEM__
