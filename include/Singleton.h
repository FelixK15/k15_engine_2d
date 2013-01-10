#pragma once

#ifndef __SINGLETON__
#define __SINGLETON__

#include "DLL_Header.h"

namespace K15_Engine
{
	template <class T>
	class K15ENGINE_API Singleton
	{
	public:
		Singleton()
		{
			#if defined( _MSC_VER ) && _MSC_VER < 1200	 
				int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
				m_instance = (T*)((int)this + offset);
			#else
				m_instance = static_cast< T* >( this );
			#endif
		};
	
		virtual ~Singleton()
		{
			m_instance = 0;
		};
	
		static T *getInstance()
		{	
			if(!m_instance){
				m_instance = new T();
			}
			return (m_instance);
		}
	
		static void del(){
			if(m_instance){
				delete m_instance;
				m_instance = 0;
			}
		}
	
	protected:
		static T *m_instance;
	};
}
#endif //__SINGLETON__
