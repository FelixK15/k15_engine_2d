#include "GameWorldFactory.h"
#include "Resource.h"
#include "TiledGameWorldCreator.h"

using namespace K15_Engine;

bool GameWorldFactory::createWorld(GameWorld& gameWorld,Resource *res)
{
	if(res != NULL){
		String appendix = res->getName().substr(res->getName().length() - 3,3);
		
		if(appendix == "tmx"){
			TiledGameWorldCreator creator(gameWorld,res);

			return creator.create();
		}
	}

	return false;
}
