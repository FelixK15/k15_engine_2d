#include "GameWorldState.h"
#include "GameWorld.h"
#include "Log.h"

using namespace K15_Engine;

GameWorldState::GameWorldState()
{
	m_gameworld = NULL;
}

GameWorldState::~GameWorldState()
{
	SAFE_DELETE(m_gameworld);
}

void GameWorldState::update(U32 deltaTime)
{
	m_gameworld->update(deltaTime);
}

bool GameWorldState::setGameWorld( GameWorld gameworld )
{
	if(m_gameworld != NULL){
		SAFE_DELETE(m_gameworld);
		m_gameworld = NULL;
	}

	m_gameworld = new GameWorld(gameworld);

	return true;
}