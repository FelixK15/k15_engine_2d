/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Class for representing the Resource Manager.
 * Use this class to load and cache Resources.
 */

#pragma once

#ifndef __RESOURCEMANAGER__
#define __RESOURCEMANAGER__

#include "Event.h"

#include "Resource.h"
#include "IResourceFile.h"

namespace K15_Engine
{
	typedef std::map<String,Resource*> ResourceCache;
	
	class K15ENGINE_API ResourceManager
	{
	public:
	
		/**
		* Standard Constructor.
		*/
		ResourceManager();
	
		/**
		* Standard Destructor.
		*/
		~ResourceManager();
	
		/**
		* Opens the resource file for read access.
		*
		*
		* @return bool - true if file is open and false if an error occured.
		*/
		bool openResourceFile();
	
		/**
		* Closes the resource file (No more read access will be granted after the call of this method.)
		* Read access will be granted again after openResourceFile() is called.
		*
		* @return bool - true if the file is closed and false if an error occured.
		*/
		bool closeResourceFile();

		/**
		* A resource with the specific name will get cached.
		* A call to this method involes opening, reading and closing of the resource file.
		*
		* @param  name - Name of the resource within the resource file.
		*
		* @return bool - true if the resource could get cached and false if not.
		*/
		bool cacheResource(const String& name);
	
		/**
		* Checks if a resource with the given name has been loaded in the cache.
		*
		* @param  identifier - Name of the resource.
		*
		* @return bool - true if resource is in the cache and false if not.
		*/
		bool isResourceInCache(const String& name);

		/**
		* A resource with the given name will get cached and returned.
		* If the resource already got cached previously the resource will just
		* get returned but if the resource wasn't cached previously a call to this
		* method will involve opening, reading and closing the resource file. (The resource will get cached afterwards)
		*
		* @param  name - Name of the resource within the resource file.
		*
		* @return Resource* - Resource object if successful or NULL if resource could not get read.
		*/
		Resource *getResource(const String& name);
	
	private:
		
		/**
		* Internal function that reads the resource file.
		*/
		Resource *_loadResource(String &identifier);
	
		bool _addResourceToCache(Resource *resource);
	
		ResourceCache m_cache;
	
		IResourceFile *m_resourceFile;
	
	};
}

#endif //__RESOURCEMANAGER