// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFlow/Public/GameModeFSM.h"
#include "Controllers/Public/UIPlayerController.h"
#include "Controllers/Public/MatchPlayerController.h"
#include "BombermanLikeGameModeBase.generated.h"


/*! \brief Type that represents what a cell in the map can contain
*
* This type represents the things that can be places in a cell of the map
*/
UENUM(BlueprintType)
enum class EMatchResult : uint8
{
	ResultDraw,
	ResultPlayer1,
	ResultPlayer2
};

/*! \brief Main Game Mode for the Bomberman-Like game
 * 
 * This class will manage the state of the game,
 * creating each new game session
 *
 */
UCLASS()
class BOMBERMANLIKE_API ABombermanLikeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameState)
	int NumPlayers;

	/*! \brief Returns current state
	 *
	 * Returns current state of the game
	 */
	UFUNCTION(BlueprintCallable, Category = GameState)
	EGameModeStates GetCurrentState() const;

	/*! \brief Notifies the Game Mode that the Splash Screen has finished
	 *
	 * Notifies the Game Mode that the Splash Screen has finished and that it should act accordingly
	 */
	UFUNCTION(BlueprintCallable, Category = GameState)
	void NotifyEndSplash();

	/*! \brief Notifies the Game Mode that the Character Selection has finished
	*
	* Notifies the Game Mode that the Character Selection has finished and that it should act accordingly
	*/
	UFUNCTION(BlueprintCallable, Category = GameState)
	void NotifyEndCharacterSelection();

	/*! \brief Notifies the Game Mode that the End Match has finished
	*
	* Notifies the Game Mode that the End Match has finished and that it should act accordingly
	*/
	UFUNCTION(BlueprintCallable, Category = GameState)
	void NotifyEndEndMatch();

	/*! \brief Notifies the Game Mode wich player was alive
	*
	* Pass the game mode the info of wich player was alive at the end of the match so it can calculate the result
	*/
	UFUNCTION(BlueprintCallable, Category = GameState)
	void NotifyPlayerStatusAfterMatch(bool bIsPlayer1Alive, bool bIsPlayer2Alive);

	/*! \brief Returns the result of the last match
	*
	* Returns Draw if both where killed or the time run out, or the Player who won
	*/
	UFUNCTION(BlueprintCallable, Category = GameState)
	EMatchResult GetLastMatchResult() const;

	/*! \brief Returns the score for the passed player
	*
	* Returns the total score for the player passed as a parameter
	*/
	UFUNCTION(BlueprintCallable, Category = GameState)
	int GetScore(int player) const;

	/*! \brief Swaps between player controllers
	 *
	 * Swap the player controller of a pawn
	 */
	UFUNCTION(BlueprintCallable, Category = PlayerController)
	static void SwapPlayerController(APawn* pawn, APlayerController* newPlayerController);

	/*! \brief Clears the input so the keys are not pressed anymore
	*
	* Clears the input so the key strokes don't pass from one state to the other
	*/
	UFUNCTION(BlueprintCallable, Category = PlayerController)
	static void ClearInputFromController(APlayerController* controller);

	ABombermanLikeGameModeBase();		//<! Constructor
	~ABombermanLikeGameModeBase();		//<! Destructor

	virtual void Tick(float DeltaSeconds) override; //<! Function called every frame

protected:
	virtual void BeginPlay() override;				//<! Called when the game starts or when spawned

private:
	GameModeFSM* m_gameState; //<! Main State of the game

	EMatchResult m_lastMatchResult;	//<! The last result for the previous match
	int m_scorePlayer1;		//<! Stores the total score of player 1
	int m_scorePlayer2;		//<! Stores the total score of player 2
};
