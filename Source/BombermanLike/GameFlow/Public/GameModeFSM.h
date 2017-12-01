// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "Tools/FSM/Public/FSM.h"

/////////////////////////////////////////////////
///FORWARD DECLARATIONS
/////////////////////////////////////////////////
class ABombermanLikeGameModeBase;
class AUIPlayerController;
class AMatchPlayerController;

/*! \brief Enum that represents the high level states of the game.
 *
 * Enum representing the different states of the game, being these:
 * - Splash, a splash screen with the main title.
 * - CharacterSelection, a screen where we can select a character and select the number of players.
 * - Match, the main playable part where the players try to kill each other using bombs.
 * - EndMatch, where the winner of the match is presented.
 */
UENUM(BlueprintType)
enum EGameModeStates
{
	Splash,
	CharacterSelection,
	Match,
	EndMatch,

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

	void Initialize(ABombermanLikeGameModeBase* gameMode);	//!< Sets the needed variables to manage states
private:
	void InitializeFunctions();		//!< Initializes the managing functions for the states

	void BeginSplash(EGameModeStates previousState);		//!< Method called at the begining of the state
	void UpdateSplash(float DeltaTime);						//!< Method called each frame while in the state
	void EndSplash(EGameModeStates nextState);				//!< Method called at the end of the state

	void BeginCharacterSelection(EGameModeStates previousState);		//!< Method called at the begining of the state
	void UpdateCharacterSelection(float DeltaTime);						//!< Method called each frame while in the state
	void EndCharacterSelection(EGameModeStates nextState);				//!< Method called at the end of the state

	void BeginMatch(EGameModeStates previousState);			//!< Method called at the begining of the state
	void UpdateMatch(float DeltaTime);						//!< Method called each frame while in the state
	void EndMatch(EGameModeStates nextState);				//!< Method called at the end of the state

	void BeginEndMatch(EGameModeStates previousState);			//!< Method called at the begining of the state
	void UpdateEndMatch(float DeltaTime);						//!< Method called each frame while in the state
	void EndEndMatch(EGameModeStates nextState);				//!< Method called at the end of the state

	ABombermanLikeGameModeBase* m_gameMode;					//!< Holds a reference to the current game mode
	TArray<AUIPlayerController*> m_UIControllers;			//!< Holds a reference to UI controllers when these exist
	TArray<AMatchPlayerController*> m_matchControllers;		//!< Holds a reference to the Match controllers when these exist

	float m_matchTimer;										//!< The time left for the match to end
};