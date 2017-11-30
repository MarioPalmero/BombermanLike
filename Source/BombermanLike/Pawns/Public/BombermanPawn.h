// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BombermanPawn.generated.h"

/////////////////////////////////////////////////
///FORWARD DECLARATIONS
/////////////////////////////////////////////////
class USphereComponent;
class UPawnMovementComponent;
class UDamageableComponent;
class AMapManager;

/////////////////////////////////////////////////
///DELEGATES
/////////////////////////////////////////////////

/*! \brief Class that represents a Bomberman
 *
 * Bomberman controlled by the player or by the AI
 */
UCLASS()
class BOMBERMANLIKE_API ABombermanPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bombs)
	int BombAmount;		//<! Component for managing damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bombs)
	UClass* BombClass;		//<! Class for the bomb

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	UDamageableComponent* DamageableComponent;		//<! Component for managing damage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed;		//<! Measures the amount of space for time unit that the pawn can move

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bombs)
	float FlameLength;		//<! Measures the length of the flames for the bombs placed by this pawn
	
	/*! \brief Moves the pawn
	 *
	 * Using the input delta this function moves the indicated amount the pawn
	 */
	UFUNCTION(BlueprintCallable, Category = Movemet)
	void Move(FVector movementAmount);

	/*! \brief Places a bomb
	*
	* If there are more bombs left to be able to be placed, the pawn will place one
	*/
	UFUNCTION(BlueprintCallable, Category = Movemet)
	void PlaceBomb();

	/*! \brief Increments the max number of bombs the pawn can place
	*
	* Increment the max number of bombs the pawn can place and also the current bombs left
	*/
	UFUNCTION(BlueprintCallable, Category = Movemet)
	void IncreaseMaxNumberOFBombs(int amount);

	/*! \brief Recovers a bomb that was placed so it can be placed again
	*
	* Once a bomb has explode we can place another one again
	*/
	UFUNCTION(BlueprintCallable, Category = Movemet)
	void RecoverBomb(UExplodableComponent* explodable);

	/*! \brief Resets the max number of bombs to the base amount
	*
	* Resets the max number of bombs to the base amount
	*/
	UFUNCTION(BlueprintCallable, Category = Movemet)
	void ResetMaxBombs();
	
	ABombermanPawn();	//<! Constructor

	virtual void Tick(float DeltaTime) override;	//<! Called every frames

	virtual void PossessedBy(AController* NewController) override;	//<! Called when the pawn is possessed by a controller
protected:
	virtual void BeginPlay() override;	//<! Called when the game starts or when spawned

private:
	USphereComponent*	m_collisionComponent;		//<! Collision component for this pawn
	UPawnMovementComponent* m_movementComponent;	//<! Movement Component create in this pawn

	int m_currentBombsMax;							//<! Maximum number of bombs this pawn can place
	int m_currentBombsLeft;							//<! Current number of bombs this pawn can place
};
