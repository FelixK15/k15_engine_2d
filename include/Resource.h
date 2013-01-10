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
 * Class for representing resources loaded from the resource file.
 */

#pragma once

#ifndef __RESOURCE__
#define __RESOURCE__

#include "StandardIncludes.h"
#include "Event.h"

namespace K15_Engine
{
	class K15ENGINE_API Resource
	{
	
	friend class ResourceManager;
	
	public:
	
		/**
		* Standard constructor.
		*/
		Resource();

		/**
		* Constructor
		*
		* @param  name - Name of the resource.
		* @param  content - Content in bytes.
		* @param  size - Size of the content.
		*/
		Resource(const String& name,byte *content,int size);

		/**
		* Constructor
		*
		* @param  name - Name of the resource.
		* @param  size - Appendix of the resource file
		* @param  content - Content in bytes.
		* @param  size - Size of the content.
		*/
		Resource(const String& name,const String& appendix,byte *content,int size);

		/**
		* Copy Construcot.
		* Everything except the Resource ID will get copied;
		*/
		Resource(Resource const &otherResource);
	
		/**
		* Standard Destructor
		*/
		~Resource();

		/**
		* Returns the ID of the resource.
		*
		*
		* @return int - Resource ID.
		*/
		int getID() const;
	
		/**
		* Returns the name of the resource (=filename)
		*
		*
		* @return const String& - Name of the resource.
		*/
		const String& getName() const;

		/**
		* Returns the appendix of the resource (=filename appendix)
		*
		*
		* @return const String& - Appendix of the resource.
		*/
		const String& getAppendix() const;

		/**
		* Returns the size of this resource.
		*
		*
		* @return int - Size of the resource
		*/
		int getSize() const;

		/**
		* Returns this content of this resource in byte.
		*
		*
		* @return byte* - Content of the resource in byte.
		*/
		byte *getContent() const;

		/**
		* Is the resource empty?
		*
		*
		* @return bool - true if the resource is empty or false if not.
		*/
		bool isEmpty() const;
	
	private:
		const int m_resourceID;
		const int m_size;
		const String m_name;
		const String m_appendix;
		byte *m_content;
	};
}

#endif //__RESSOURCE__