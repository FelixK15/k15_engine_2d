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

#ifndef __USEFUL_MAKROS__
#define __USEFUL_MAKROS__

#define M_HAS_ITEM(map,expr) map.find(expr) != map.end()

#define PERFORM_ON_POINTER_IF_NOT_NULL(ptr,expr) if(ptr) ptr->expr

#define DO_IF_POINTER_NULL(ptr,expr) if(!ptr) expr

#define DO_IF_POINTER_NOT_NULL(ptr,expr) if(ptr) expr

#endif //__USEFUL_MAKROS__