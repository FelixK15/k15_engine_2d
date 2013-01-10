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
 * 
 */
#pragma once

#ifndef __ABSTRACT_SYSTEMMANAGER__
#define __ABSTRACT_SYSTEMMANAGER__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API AbstractSystemManager
	{

	public:

		virtual int getTick() = 0;

		virtual void sleep(int milliseconds) = 0;

		virtual std::vector<String> getFilesFromDirectory(const String& directory,const String& filter = "*.*",bool addDirectoryToFileName = true) = 0;
	};
}

#endif //__ABSTRACT_SYSTEMMANAGER__