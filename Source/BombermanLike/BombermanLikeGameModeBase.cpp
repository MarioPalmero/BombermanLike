// - Mario Palmero [2017], zlib/libpng licensed.

#include "BombermanLikeGameModeBase.h"

ABombermanLikeGameModeBase::ABombermanLikeGameModeBase() : Super()
{

	// Following RAII we initialize and destroy resources properly
	m_gameState = new GameModeFSM();
}

ABombermanLikeGameModeBase::~ABombermanLikeGameModeBase()
{
	Super();

	// Following RAII we initialize and destroy resources properly
	delete m_gameState;
}

EGameModeStates ABombermanLikeGameModeBase::GetCurrentState() const
{
	return m_gameState->GetCurrentState();
}

void ABombermanLikeGameModeBase::Tick(float DeltaSeconds)
{
	m_gameState->Update(DeltaSeconds);
}
