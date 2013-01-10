#pragma once

#ifndef __DATETIME__
#define __DATETIME__

#include "StandardIncludes.h"

namespace K15_Engine
{
	class K15ENGINE_API DateTime
	{

	public:

		DateTime();

		~DateTime();

		const String toDateString() const;

		const String toShortDateString() const;

		const String getYear() const;

		const String getMonth() const;

		const String getDay() const;

		const String getHour() const;

		const String getMinute() const;

		const String getSecond() const;

	private:
		String m_year;
		String m_month;
		String m_day;
		String m_hour;
		String m_minute;
		String m_second;
	};
}

#endif //__DATETIME__