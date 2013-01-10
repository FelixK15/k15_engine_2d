#pragma once

#ifndef __DLL_HEADER__
#define __DLL_HEADER__

	#if defined(_WIN32)
		#ifdef _ENGINE_BUILD_DLL_
			#define K15ENGINE_API __declspec(dllexport)
		#else
			#ifdef __STATICBUILD__
				#define K15ENGINE_API	
			#else
				#define K15ENGINE_API __declspec(dllimport)
			#endif
		#endif
	#endif

#endif