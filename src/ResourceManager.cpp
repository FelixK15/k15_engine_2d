#include "ResourceManager.h"
#include "EventManager.h"
#include "ZipResourceFile.h"
#include "Events.h"
#include "Log.h"

using namespace K15_Engine;

template<> ResourceManager* Singleton<ResourceManager>::m_instance = 0;

ResourceManager::ResourceManager()
{
	m_resourceFile = new ZipResourceFile();
}

ResourceManager::~ResourceManager()
{
	SAFE_DELETE(m_resourceFile);

	m_cache.clear();
}

Resource *ResourceManager::getResource( const String& identifier)
{
	//if the resource can be find in the cache, it will be returned.
	if(isResourceInCache(identifier)){
		return m_cache[identifier];
	}

	//If the resource isn't in the cache it must be read from the resource file first.
	Resource *res = m_resourceFile->getResource(identifier);

	//Checks if the resource could be read successful.
	if(res == NULL){
		WRITE_CRITICALLOG("Resource with the name \"" + identifier + "\" is empty.");
	}

	return res;
}

bool ResourceManager::openResourceFile()
{
	WRITE_DEBUG("About to open resourcefile.");
	ResourceFileStatus status = m_resourceFile->open();
	if(status == RESOURCEFILE_ERROR_OPEN){
		WRITE_CRITICALLOG("Couldn't open resourcefile!");
	}else if(status == RESOURCEFILE_NOT_FOUND){
		WRITE_CRITICALLOG("Resourcefile not found.");
	}else if(status == RESOURCEFILE_ALREADY_OPEN){
		WRITE_ERRORLOG("Resourcefile already open.");
	}

	return status == RESOURCEFILE_SUCCESSFULLY_OPEN;
}

bool ResourceManager::closeResourceFile()
{
	WRITE_DEBUG("About to close resourcefile.");
	return m_resourceFile->close();
}

bool ResourceManager::cacheResource(const String& identifier)
{
	//Checks if the Resource is maybe already in the cache.
	if(!isResourceInCache(identifier)){
		//If the Resource is not in the cache, it will get read from the resource file.
		Resource *resource = m_resourceFile->getResource(identifier);

		if(resource == NULL || !_addResourceToCache(resource)){
			WRITE_ERRORLOG("Failed to add the resource \"" + identifier + "\" to the resourcecache.");
			return false;
		}

		return true;
	}

	WRITE_ERRORLOG("Resource \"" + identifier+ "\" already added to the cache.");
	return false;
}

bool ResourceManager::isResourceInCache(const String& identifier)
{
	return m_cache.find(identifier) != m_cache.end();
}

bool ResourceManager::_addResourceToCache( Resource *resource )
{
	if(m_cache.find(resource->getName()) != m_cache.end()){
		WRITE_ERRORLOG("Resource \"" + resource->getName() + "\" already added to the cache.");
		return false;
	}

	m_cache[resource->getName()] = resource;

	NEW_EVENT_WITH_1_ARG(Events::ResourceCached,"ID",resource->getID());
	ADD_NEW_EVENT_TO_EVENTQUEUE();

	return true;
}
