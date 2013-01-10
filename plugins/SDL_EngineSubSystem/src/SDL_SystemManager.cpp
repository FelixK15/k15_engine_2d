#include "SDL_SystemManager.h"
#include "Log.h"

#include "SDL\SDL_timer.h"

#ifdef _WIN32
#include "windows.h"
#endif

using namespace K15_Engine;

SDL_SystemManager::SDL_SystemManager()
{
	WRITE_DEBUG("SDL_SystemManager created.");
}

SDL_SystemManager::~SDL_SystemManager()
{
	WRITE_DEBUG("SDL_SystemManager destroyed.");
}

int SDL_SystemManager::getTick()
{
	return SDL_GetTicks();
}

void SDL_SystemManager::sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
}

std::vector<String> SDL_SystemManager::getFilesFromDirectory( const String& directory, const String& filter,bool addDirectoryToFileName)
{
	std::vector<String> fileList;

	String searchPath;

	if(directory.at(0) != '.' || directory.at(1) != '\\'){
		searchPath = ".\\";
	}

	searchPath += directory;
	
	int lastPos = searchPath.size() - 1;
	
	if(searchPath.at(lastPos) != '\\'){
		searchPath += '\\';
	}

	String filterPath = searchPath + filter;

#ifdef _WIN32

	WIN32_FIND_DATA findDataStruct;
	HANDLE handle = FindFirstFile(filterPath.c_str(),&findDataStruct);
	if(handle != INVALID_HANDLE_VALUE){
		do{
			String file = "";
			if(addDirectoryToFileName){
				file += searchPath;	
			}
			file += findDataStruct.cFileName;

			fileList.push_back(file);
		}while(FindNextFile(handle,&findDataStruct) != 0);
	}
#endif

	return fileList;
}
