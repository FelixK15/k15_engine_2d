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
 * Interface for classes that need to load resources from a resource file.
 */

#pragma once

#ifndef __RESOURCEABLE__
#define __RESOURCEABLE__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API IResourceable
	{

	public:

		/**
		* This function is called by the ResourceManager when resource is loaded from a IResourceFile implementation
		*
		* @param resource - Object of type Resource which holds all the necessary information. 
		*
		* @return bool - true if content has been set successful and false if not.
		*/
		virtual bool setContent(Resource *resource) = 0;

		/**
		* This functions can be called if the user wants to know if a certain resource has been loaded successful.
		*
		* @return bool - true if resource has been loaded succesful and false if not.
		*/
		virtual bool loadedSuccessful() = 0;

		/**
		* Function to copy from an IResource implementation.
		*
		* @param  resourceable - IResourceable implementation.
		*
		* @return bool
		*/
		virtual bool copyFrom(IResourceable *resourceable) = 0;

	protected:
		
		
	};
}

#endif //__CLASSNAME__