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
 * Interface for Dynamic Library Implementations
 */

#pragma once

#ifndef __IDYNLIBOSSPEC__
#define __IDYNLIBOSSPEC__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API IDynLibOSSpec
	{

	public:

		/**
		* Returns the address of a certain function within a DLL.
		*
		* @param  name - Name of the function whose address shall get returned.
		*
		* @return void* - Address of the function.
		*/
		virtual void *getProcAddress(const String& name) const = 0;

		/**
		* Has the DLL been loaded successful?
		*
		*
		* @return bool - true if the DLL was loaded successful or false if not.
		*/
		virtual bool hasBeenLoaded() const = 0;

		virtual const String& getName() const = 0;

	};
}

#endif //__CLASSNAME__