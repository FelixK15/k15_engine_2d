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
 * Some useful Mathematical formulas.
 */

#pragma once

#ifndef __MATHFORMS__
#define __MATHFORMS__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API MathForms
	{
	public:

		/**
		* Converts an angle to a normed angle, an angle with the value 0 - 360 that is.
		*
		* @param  angle - "unnormed" angle. may be > 360 or < 0
		*
		* @return U16 returns normed angle between 0 and 360
		*/
		static inline U16 getConvertedAngle(int angle){ return angle > 360 ? angle % 360 : angle; }
	};
}

#endif //__MATHFORMS__