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

/*! \brief Class that represents a Bomberman
 *
 * Bomberman controlled by the player or by the AI
 */
UCLASS()
class BOMBERMANLIKE_API ABombermanPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed;		//<! MEasures the amount of space for time unit that the pawn can move

	/*! \brief Moves the pawn
	 *
	 * Using the input delta this function moves the indicated amount the pawn
	 */
	UFUNCTION(BlueprintCallable, Category = Movemet)
	void Move(FVector movementAmount);

	ABombermanPawn();	//<! Constructor

	virtual void Tick(float DeltaTime) override;	//<! Called every frames

protected:
	virtual void BeginPlay() override;	//<! Called when the game starts or when spawned

private:
	USphereComponent*	m_collisionComponent;
	UPawnMovementComponent* m_movementComponent;	//<! Movement Component create in this pawn
};
