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

	// Match functions
	SetBeginStateFunction(EGameModeStates::Match, [&](EGameModeStates e) {BeginMatch(e);});
	SetEndStateFunction(EGameModeStates::Match, [&](EGameModeStates e) {EndMatch(e);});
	SetUpdateFunction(EGameModeStates::Match, [&](float t) {UpdateMatch(t);});

	// End Game functions
	SetBeginStateFunction(EGameModeStates::EndMatch, [&](EGameModeStates e) {BeginEndMatch(e);});
	SetEndStateFunction(EGameModeStates::EndMatch, [&](EGameModeStates e) {EndEndMatch(e);});
	SetUpdateFunction(EGameModeStates::EndMatch, [&](float t) {UpdateEndMatch(t);});
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

void GameModeFSM::BeginMatch(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateMatch(float DeltaTime)
{

}

void GameModeFSM::EndMatch(EGameModeStates nextState)
{

}

void GameModeFSM::BeginEndMatch(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateEndMatch(float DeltaTime)
{

}

void GameModeFSM::EndEndMatch(EGameModeStates nextState)
{

}
