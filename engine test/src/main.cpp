#include "MyGame.h"
#include "LuaScript.h"

int main()
{
	Game *game = new LolGame();

	myGame->initialize();
	myGame->start();
	myGame->shutdown();

	return 0;
}