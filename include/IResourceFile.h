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
 * Interface for future Resource File Implementations
 * One can create a new implementation. He/She just needs to implement this Interface.
 */

#pragma once

#ifndef __IRESOURCEFILE__
#define __IRESOURCEFILE__

#include "StandardIncludes.h"

namespace K15_Engine
{
	enum ResourceFileStatus{
		RESOURCEFILE_SUCCESSFULLY_OPEN,
		RESOURCEFILE_NOT_FOUND,
		RESOURCEFILE_ERROR_OPEN,
		RESOURCEFILE_ALREADY_OPEN
	};

	class IResourceFile
	{

	public:

		/**
		* Try to open the resource file.
		*
		* @return bool - true if the resource file could be opened and false if not.
		*/
		virtual ResourceFileStatus open() = 0;

		//Returns true if the resource file is open.
		/**
		* Check if resource file is already open.
		*
		* @return bool - true if the resource file could be opened and false if not.
		*/
		virtual bool isOpen() const = 0;

		/**
		* Try to close the resource file
		*
		*
		* @return bool - true if the resource file could be closed and false if not.
		*/
		virtual bool close() = 0;

		//Attempts to read a resource file from the resource file.
		//If the attempt failed, the resources objects method isEmpty() will return true.
		/**
		* Attempt to read a Resource from the resource file.
		*
		* @param  name - Name of the Resource within the resource file.
		*
		* @return Resource* - Pointer to a Resource object or NULL if Resource could not get loaded.
		*/
		virtual Resource *getResource(const String& name) = 0;

	};
}


#endif // __IRESOURCEFILE__
