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
	int BaseBombAmount;		//<! Component for managing damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bombs)
	UClass* BombClass;		//<! Class for the bomb

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	UDamageableComponent* DamageableComponent;		//<! Component for managing damage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float BaseSpeed;		//<! Measures the amount of space for time unit that the pawn can move

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bombs)
	int BaseFlameLength;		//<! Measures the length of the flames for the bombs placed by this pawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Death)
	bool bIsDead;			//<! Indicates if the player has died
	
	/*! \brief Moves the pawn
	 *
	 * Using the input delta this function moves the indicated amount the pawn
	 */
	UFUNCTION(BlueprintCallable, Category = Movement)
	void Move(FVector movementAmount);

	/*! \brief Places a bomb
	*
	* If there are more bombs left to be able to be placed, the pawn will place one
	*/
	UFUNCTION(BlueprintCallable, Category = Bombs)
	void PlaceBomb();

	/*! \brief Increments the max number of bombs the pawn can place
	*
	* Increment the max number of bombs the pawn can place and also the current bombs left
	*/
	UFUNCTION(BlueprintCallable, Category = Bombs)
	void IncreaseMaxNumberOFBombs(int amount);

	/*! \brief Recovers a bomb that was placed so it can be placed again
	*
	* Once a bomb has explode we can place another one again
	*/
	UFUNCTION(BlueprintCallable, Category = Bombs)
	void RecoverBomb(UExplodableComponent* explodable);

	/*! \brief Resets the max number of bombs to the base amount
	*
	* Resets the max number of bombs to the base amount
	*/
	UFUNCTION(BlueprintCallable, Category = Bombs)
	void ResetMaxBombs();

	UFUNCTION(BlueprintCallable, Category = Movement)
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IncreaseCurrentSpeed(float amount);

	UFUNCTION(BlueprintCallable, Category = Bombs)
	void IncreaseFlameLength(int amount);

	/*! \brief Kills the Pawn
	*
	* Kills the Pawn, eliminating it from the match
	*/
	UFUNCTION(BlueprintCallable, Category = Death)
	void Kill();

	/*! \brief Resurrects the Pawn
	*
	* Resurrects the Pawn, resetting all its variables to default
	*/
	UFUNCTION(BlueprintCallable, Category = Death)
	void Resurrect();

	/*! \brief Sets the colour of the pawn
	 *
	 * Looks for the material of the mesh component and creates a dynamic instance assigning the colour to it
	 */
	UFUNCTION(BlueprintCallable, Category = Colour)
	void AssignColour(FColor newColour);
	
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

	float m_currentSpeed;							//<! Current speed, including pickups modiffications

	int m_currentFlameLength;						//<! Current flame length, including pickups modifications

};
