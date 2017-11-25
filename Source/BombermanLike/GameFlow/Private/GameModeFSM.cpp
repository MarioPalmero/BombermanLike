// - Mario Palmero [2017], zlib/libpng licensed.

#include "GameFlow/Public/GameModeFSM.h"


GameModeFSM::GameModeFSM() : FSM()
{
	SetState(EGameModeStates::Splash);
	InitializeFunctions();
}

GameModeFSM::GameModeFSM(EGameModeStates initialState) : FSM(initialState)
{
	InitializeFunctions();
}

void GameModeFSM::InitializeFunctions()
{
	// Splash functions
	SetBeginStateFunction(EGameModeStates::Splash, [&](EGameModeStates e) {BeginSplash(e);});
	SetEndStateFunction(EGameModeStates::Splash, [&](EGameModeStates e) {EndSplash(e);});
	SetUpdateFunction(EGameModeStates::Splash, [&](float t) {UpdateSplash(t);});

	// Character Selection functions
	SetBeginStateFunction(EGameModeStates::CharacterSelection, [&](EGameModeStates e) {BeginCharacterSelection(e);});
	SetEndStateFunction(EGameModeStates::CharacterSelection, [&](EGameModeStates e) {EndCharacterSelection(e);});
	SetUpdateFunction(EGameModeStates::CharacterSelection, [&](float t) {UpdateCharacterSelection(t);});

	// Game functions
	SetBeginStateFunction(EGameModeStates::Game, [&](EGameModeStates e) {BeginGame(e);});
	SetEndStateFunction(EGameModeStates::Game, [&](EGameModeStates e) {EndGame(e);});
	SetUpdateFunction(EGameModeStates::Game, [&](float t) {UpdateGame(t);});

	// End Game functions
	SetBeginStateFunction(EGameModeStates::EndGame, [&](EGameModeStates e) {BeginEndGame(e);});
	SetEndStateFunction(EGameModeStates::EndGame, [&](EGameModeStates e) {EndEndGame(e);});
	SetUpdateFunction(EGameModeStates::EndGame, [&](float t) {UpdateEndGame(t);});
}

void GameModeFSM::BeginSplash(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateSplash(float DeltaTime)
{

}

void GameModeFSM::EndSplash(EGameModeStates nextState)
{

}

void GameModeFSM::BeginCharacterSelection(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateCharacterSelection(float DeltaTime)
{

}

void GameModeFSM::EndCharacterSelection(EGameModeStates nextState)
{

}

void GameModeFSM::BeginGame(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateGame(float DeltaTime)
{

}

void GameModeFSM::EndGame(EGameModeStates nextState)
{

}

void GameModeFSM::BeginEndGame(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateEndGame(float DeltaTime)
{

}

void GameModeFSM::EndEndGame(EGameModeStates nextState)
{

}
