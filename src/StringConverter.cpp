#include "StringConverter.h"

using namespace K15_Engine;

String StringConverter::toString( int val )
{
	std::ostringstream sStream;
	sStream << val;
	return sStream.str();
}

String StringConverter::toString( unsigned int val )
{
	std::ostringstream sStream;
	sStream << val;
	return sStream.str();
}

String StringConverter::toString( float val)
{
	std::ostringstream sStream;
	sStream << val;
	return sStream.str();
}

String StringConverter::toString( bool val)
{
	if(val)
		return "true";
	else
		return "false";
}

int StringConverter::toInt( String val , int failValue)
{
	std::istringstream sStream(val);
	int iRet = failValue;
	sStream >> iRet;
	return iRet;
}

float StringConverter::toFloat( String val,float failValue )
{
	std::istringstream sStream(val);
	float fRet = failValue;
	sStream >> fRet;
	return fRet;
}

bool StringConverter::toBool(String val,bool failValue)
{
	if(val == "true")
		return true;
	else if(val == "false")
		return false;
	else if(val == "1")
		return true;
	else if(val == "0")
		return false;
	else
		return failValue;
}

int StringConverter::HexStringToInt(String val,int failValue)
{
	std::istringstream sStream(val);
	int iRet = failValue;
	return iRet;
}