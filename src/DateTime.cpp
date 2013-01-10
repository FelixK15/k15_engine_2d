#include "DateTime.h"
#include "StringConverter.h"

using namespace K15_Engine;

DateTime::DateTime()
{
	time_t rawTime;
	tm *timeInfo = NULL;
	time(&rawTime);
	timeInfo = localtime(&rawTime);

	int year,month,day,hour,minute,second;

	year = timeInfo->tm_year;
	month = timeInfo->tm_mon;
	day = timeInfo->tm_mday;
	hour = timeInfo->tm_hour;
	minute = timeInfo->tm_min;
	second = timeInfo->tm_sec;

	m_year = StringConverter::toString(year);
	month > 9 ? m_month = StringConverter::toString(month) : m_month = "0" + StringConverter::toString(month);
	day > 9 ? m_day = StringConverter::toString(day) : m_day = "0" + StringConverter::toString(day);
	hour > 9 ? m_hour = StringConverter::toString(hour) : m_hour = "0" + StringConverter::toString(hour);
	minute > 9 ? m_minute = StringConverter::toString(minute) : m_minute = "0" + StringConverter::toString(minute); 
	second > 9 ? m_second = StringConverter::toString(second) : m_second = "0" + StringConverter::toString(second);
}

DateTime::~DateTime()
{

}

const String DateTime::toDateString() const
{
	return m_day + String(".") + m_month + String(".") + m_year + String(" | ") + m_hour + String(":") + m_minute + String(":") + m_second;
}

const String DateTime::toShortDateString() const
{
	return m_hour + String(":") + m_minute + String(":") + m_second;
}

const String DateTime::getYear() const
{
	return m_year;
}

const String DateTime::getMonth() const
{
	return m_month;
}

const String DateTime::getDay() const
{
	return m_day;
}

const String DateTime::getHour() const
{
	return m_hour;
}

const String DateTime::getMinute() const
{
	return m_minute;
}

const String DateTime::getSecond() const
{
	return m_second;
}
