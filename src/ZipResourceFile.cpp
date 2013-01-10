#include "ZipResourceFile.h"
#include "Resource.h"
#include "EventManager.h"
#include "Events.h"
#include "Log.h"

using namespace K15_Engine;

ZipResourceFile::ZipResourceFile()
{
	m_zipHandle = NULL;
}

ZipResourceFile::~ZipResourceFile()
{
	//If the file is still open at destruction time,
	//it will get closed here.
	if(isOpen()){
		close();
	}

	//Handle gets deleted here.
	SAFE_DELETE(m_zipHandle);
}

ResourceFileStatus ZipResourceFile::open()
{
	//if the handle is not NULL, that means that the file is currently open.
	if(m_zipHandle){
		return RESOURCEFILE_ALREADY_OPEN;
	}

	//handle gets determined
	m_zipHandle = unzOpen("resourcepak.kpk");

	//Check if the archive got opened properly.
	if(!m_zipHandle)
	{
		return RESOURCEFILE_ERROR_OPEN;
	}

	return RESOURCEFILE_SUCCESSFULLY_OPEN;
}

bool ZipResourceFile::isOpen() const
{
	return m_zipHandle != NULL;
}

bool ZipResourceFile::close()
{
	//if the handle is NULL, that means that the file is already closed.
	if(!m_zipHandle){
		WRITE_LOG("ResourceFile already closed!");
		return false;
	}

	//attempt to close the zip file.
	unzCloseCurrentFile(m_zipHandle);

	//Check if the file got closed properly.
	if(unzClose(m_zipHandle) != UNZ_OK){
		WRITE_ERRORLOG("Resourcefile was not closed.");
		return false;
	}

	m_zipHandle = NULL;

	return true;
}

Resource *ZipResourceFile::getResource( const String& name )
{
	//temp help variable that saves if the resource file is already open.
	bool wasOpened = true;

	//If the handle is not NULL, the file was already opened.
	if(!m_zipHandle){
		wasOpened = false;
		
		//If the file wasn't opened it will get opened here.
		if(open() != RESOURCEFILE_SUCCESSFULLY_OPEN){
			return NULL;
		}
			
	}

	//Attempt to locate the archive.
	if(unzLocateFile(m_zipHandle,name.c_str(),2) != UNZ_OK){
		WRITE_CRITICALLOG("Couldn't find resource '" + name + "'");
		close();
		return NULL;
	}

	//Try to open the archive.
	if(unzOpenCurrentFile(m_zipHandle) != UNZ_OK){
		WRITE_CRITICALLOG("Couldn't open resource '" + name + "'");
		close();
		return NULL;
	}

	unz_file_info resourceInfo;

	//Try to read the specific resource file within the archive.
	if(unzGetCurrentFileInfo(m_zipHandle,&resourceInfo,const_cast<char*>(name.c_str()),0,NULL,0,NULL,0) != UNZ_OK){
		WRITE_CRITICALLOG("Couldn't retrieve information about the resourcefile.");
		close();
		return NULL;
	}

	//buffer with the size of the size of the uncompressed file gets created.
	byte *buffer = new byte[resourceInfo.uncompressed_size];

	//resource file gets read and transfered into the buffer.
	unzReadCurrentFile(m_zipHandle,buffer,resourceInfo.uncompressed_size);

	//Resource object gets created.
	Resource *demandedResource = new Resource(name,buffer,resourceInfo.uncompressed_size);

	//If the resource file wasn't opened before this method was called, it will get closed again here.
	if(!wasOpened){
		close();
	}
		
	//Event gets fired that a resource got created.
	NEW_EVENT_WITH_1_ARG(Events::ResourceCreated,"resourceID",demandedResource->getID());
	ADD_NEW_EVENT_TO_EVENTQUEUE();

	return demandedResource;
}