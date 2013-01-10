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

#ifndef __TYPES__
#define __TYPES__

#if defined(_WIN32)
#ifdef __DLLBUILD__
#define K15ENGINE_API __declspec(dllexport)
#else
#define K15ENGINE_API __declspec(dllimport)
#endif

#ifdef __STATICBUILD__
#define K15ENGINE_API	
#endif
#endif

//Standard includes.
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <list>
#include <cassert>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <cmath>
#include <memory>
#include <cassert>
#include <functional>
#include <time.h>


#endif //__TYPES__