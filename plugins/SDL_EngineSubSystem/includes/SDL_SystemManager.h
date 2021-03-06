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

#ifndef __SDL_SYSTEMMANAGER__
#define __SDL_SYSTEMMANAGER__

#include "StandardIncludes.h"
#include "AbstractSystemManager.h"

namespace K15_Engine
{
	class SDL_SystemManager : public AbstractSystemManager
	{
	public:

		SDL_SystemManager();

		virtual ~SDL_SystemManager();

		virtual int getTick();

		virtual void sleep(int milliseconds);

		virtual std::vector<String> getFilesFromDirectory(const String& directory,const String& filter,bool addDirectoryToFileName);
	};
}

#endif //__SDL_SYSTEMMANAGER__