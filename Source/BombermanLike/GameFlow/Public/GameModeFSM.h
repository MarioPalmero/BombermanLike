// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "Tools/FSM/Public/FSM.h"

/*! \brief Enum that represents the high level states of the game.
 *
 * Enum representing the different states of the game, being these:
 * - Splash, a splash screen with the main title.
 * - CharacterSelection, a screen where we can select a character and select the number of players.
 * - Game, the main playable part where the players try to kill each other using bombs.
 * - EndGame, where the winner of the match is presented.
 */
UENUM(BlueprintType)
enum EGameModeStates
{
	Splash,
	CharacterSelection,
	Game,
	EndGame,

	GameModeStates_MAX
};

/*! \brief A FSM that represents the states of the game.
* 
* The FSM representing the states of the game,
* in charge of initializing each state and updating them.
*/
class GameModeFSM : public FSM<EGameModeStates, EGameModeStates::GameModeStates_MAX>
{
public:
	GameModeFSM();								//!< Constructor
	GameModeFSM(EGameModeStates initialState);	//!< Constructor
private:
	void InitializeFunctions();	//!< Initializes the managing functions for the states

	void BeginSplash(EGameModeStates previousState);		//!< Method called at the begining of the state
	void UpdateSplash(float DeltaTime);					//!< Method called each frame while in the state
	void EndSplash(EGameModeStates nextState);			//!< Method called at the end of the state

	void BeginCharacterSelection(EGameModeStates previousState);		//!< Method called at the begining of the state
	void UpdateCharacterSelection(float DeltaTime);					//!< Method called each frame while in the state
	void EndCharacterSelection(EGameModeStates nextState);			//!< Method called at the end of the state

	void BeginGame(EGameModeStates previousState);		//!< Method called at the begining of the state
	void UpdateGame(float DeltaTime);					//!< Method called each frame while in the state
	void EndGame(EGameModeStates nextState);				//!< Method called at the end of the state

	void BeginEndGame(EGameModeStates previousState);		//!< Method called at the begining of the state
	void UpdateEndGame(float DeltaTime);					//!< Method called each frame while in the state
	void EndEndGame(EGameModeStates nextState);				//!< Method called at the end of the state
};