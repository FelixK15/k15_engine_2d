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
 * Interface for Font implementations
 */

#pragma once

#ifndef __IFONT__
#define __IFONT__

#include "StandardIncludes.h"
#include "IResourceable.h"
#include "Resource.h"

namespace K15_Engine
{
	class K15ENGINE_API IFont : public IResourceable
	{
	public:
		
		virtual ~IFont(){};

		/**
		* Changes the size of the font.
		* Has direct influence of the ACTUAL font size.
		*
		* @param  size - new size of the font.
		*/
		virtual void setSize(U8 size) = 0;

		/**
		* returns size of the font.
		*
		*
		* @return U8 - size of the font.
		*/
		virtual U8 getSize() const = 0;	
	};
}

#endif //__IFONT__
