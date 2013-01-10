#include "Debug.h"

using namespace K15_Engine;

const int Debug::NEXT_FREE_ID = -1;
bool Debug::activated = false;

namespace{
	int max_id = 0;
	DebugStringList debugStrings;
}

void Debug::update(U32 deltaTime)
{
	Position startPos(0,500);
	for (DebugStringList::iterator i = debugStrings.begin(); i != debugStrings.end() ; i++){
		(*i).setPosition(startPos);
		(*i).update(deltaTime);
		startPos.setY(startPos.getY() + 8);
	}

	debugStrings.clear();
}

void Debug::drawAlignedDebugString( const String& string)
{
	if(Debug::activated){

		debugStrings.push_back(DrawableString(string));
	}
}
