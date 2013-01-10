#include "Event.h"

using namespace K15_Engine;

Event::Event( const String& identifier )
: m_type(identifier.c_str())
{

}

Event::Event(EventType identifier )
: m_type(identifier)
{
	m_type = identifier;
}

Event::Event(const Event& otherEvent)
	: m_type(otherEvent.m_type)
{
	m_arguments = otherEvent.m_arguments;
}

Event::~Event()
{

}

EventType Event::getType() const
{
	return m_type;
}

Variant Event::getArgument( String const &argument ) const
{
	if(m_arguments.find(argument) == m_arguments.end())
	{
		return Variant();
	}

	return m_arguments.at(argument);
}

Variant Event::getArgument(const char* argument) const
{
	return getArgument(String(argument));
}

void Event::setArgument( String const &argument,Variant &value )
{
	if(m_arguments.find(argument) == m_arguments.end())
	{
		m_arguments[argument] = value;
	}
}

void Event::setArgument( const char* argument,Variant &value )
{
	setArgument(String(argument),value);
}

bool Event::operator<( const Event & otherEvent ) const
{
	return this->m_type.m_identifier < otherEvent.m_type.m_identifier;
}

bool Event::operator==( const Event & otherEvent ) const
{
	return this->m_type.m_identifier == otherEvent.m_type.m_identifier;
}
