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
 * Implementation of the Interface IResourceFile
 * This Implementation supports reading resources from any zip supported archive.
 */
#pragma once

#ifndef __ZIPRESOURCEFILE__
#define __ZIPRESOURCEFILE__

#include "IResourceFile.h"
#include "miniZip\unzip.h"

typedef unzFile ZipHandle;

namespace K15_Engine
{
	class ZipResourceFile 
		: public IResourceFile
	{

	public:
		ZipResourceFile();

		~ZipResourceFile();

		ResourceFileStatus open();

		bool isOpen() const;

		bool close();

		Resource *getResource(const String& name);

	private:
		ZipHandle m_zipHandle;

	};
}

#endif // __ZIPRESOURCEFILE__
