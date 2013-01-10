#include "HashedString.h"

using namespace K15_Engine;

HashedString::HashedString( const char * string )
	: m_identifier(createIdentifier(string)),
	m_string(string)
{

}

HashedString::~HashedString()
{

}

U32 HashedString::getIdentifier() const
{
	return reinterpret_cast<U32>(m_identifier);
}

const char* HashedString::getString()
{
	return m_string.c_str();
}

bool HashedString::operator< (HashedString const & otherString ) const
{
	return this->getIdentifier() < otherString.getIdentifier();
}

bool HashedString::operator== ( HashedString const & otherString )
{
	return this->getIdentifier() == otherString.getIdentifier();
}

void * HashedString::createIdentifier(const char* string )
{
#define DO1(buf,i) {s1 += tolower(buf[i]); s2 += s1;}
#define DO2(buf,i) DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i) DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i) DO4(buf,i); DO4(buf,i+4);
#define DO16(buf) DO8(buf,0); DO8(buf,8);
#define BASE 65521L
#define NMAX 5552

	if(!string)
		return NULL;

	U32 s1 = 0;
	U32 s2 = 0;

	for(U32 len = strlen(string);len > 0;)
	{
		U32 k = len < NMAX ? len : NMAX;
		len -= k;
		while(k >= 16)
		{
			DO16(string);
			string += 16;
			k -= 16;
		}

		if(k != 0) do
		{
			s1 += *string++;
			s2 += s1;
		} while(--k);

		s1 %= BASE;
		s2 %= BASE;

	}

#pragma warning(push)
#pragma warning(disable : 4312)

	return reinterpret_cast<void*>((s2 << 16) | s1);

#pragma warning(pop)
#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16

}

