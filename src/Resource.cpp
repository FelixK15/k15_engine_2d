#include "Resource.h"

using namespace K15_Engine;

U32 createUniqueResourceID()
{
	static int ResourceID = 0;
	return ResourceID++;
}

Resource::Resource()
	: m_resourceID(createUniqueResourceID()),
	  m_size(0),
	  m_content(NULL),
	  m_name(""),
	  m_appendix("")
{

}

Resource::Resource(const String& name,byte *content,int size)
		: m_resourceID(createUniqueResourceID()),
		  m_content(content),
		  m_size(size),
		  m_name(name),
		  m_appendix("")
{

}

Resource::Resource(const String& name,const String& appendix,byte *content,int size)
	: m_resourceID(createUniqueResourceID()),
	m_content(content),
	m_size(size),
	m_name(name),
	m_appendix(appendix)
{

}


Resource::Resource( Resource const &otherResource )
	: m_resourceID(createUniqueResourceID()),
	  m_name(otherResource.m_name),
	  m_content(otherResource.m_content),
	  m_size(otherResource.m_size)
{
	//Everything except the ID will get copied.
}

Resource::~Resource()
{
	//Content will get deleted.
	SAFE_DELETE(m_content);
}

int Resource::getID() const
{
	return m_resourceID;
}

const String& Resource::getName() const
{
	return m_name;
}

int Resource::getSize() const
{
	return m_size;
}

byte *Resource::getContent() const
{
	return m_content;
}

bool Resource::isEmpty() const
{
	return m_content == NULL;
}
