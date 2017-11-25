// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFlow/Public/GameModeFSM.h"
#include "BombermanLikeGameModeBase.generated.h"

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
	/*! \brief Returns current state
	*
	* Returns current state of the game
	*/
	UFUNCTION(BlueprintCallable, Category = GameState)
	EGameModeStates GetCurrentState() const;

	ABombermanLikeGameModeBase();
	~ABombermanLikeGameModeBase();

	virtual void Tick(float DeltaSeconds) override; //<! Function called every frame
private:
	GameModeFSM* m_gameState; //<! Main State of the game
};
